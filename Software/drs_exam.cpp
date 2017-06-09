/********************************************************************\

  Name:         drs_exam.cpp
  Created by:   Stefan Ritt

  Contents:     Simple example application to read out a DRS4
                evaluation board

  $Id: drs_exam.cpp 21308 2014-04-11 14:50:16Z ritt $

  Modified from the above code provided for the DRS4 evaluation board

\********************************************************************/

#include <math.h>

#ifdef _MSC_VER

#include <windows.h>

#elif defined(OS_LINUX)

#define O_BINARY 0

#include <unistd.h>
#include <ctype.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <errno.h>

#define DIR_SEPARATOR '/'

#endif

#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <string.h>
#include <stdlib.h>

#include "strlcpy.h"
#include "DRS.h"

/*------------------------------------------------------------------*/
typedef struct {
    unsigned short Year;
    unsigned short Month;
    unsigned short Day;
    unsigned short Hour;
    unsigned short Minute;
    unsigned short Second;
    unsigned short Milliseconds;
} TIMESTAMP;

int main()
{
   int i, j, nBoards;
   DRS *drs;
   DRSBoard *b;
   float time_array[8][1024];
   float wave_array[8][1024];

   int number_of_events = 10000; 

   /* do initial scan */
   drs = new DRS();

   /* show any found board(s) */
   for (i=0 ; i<drs->GetNumberOfBoards() ; i++) {
      b = drs->GetBoard(i);
      printf("Found DRS4 evaluation board, serial #%d, firmware revision %d\n", 
         b->GetBoardSerialNumber(), b->GetFirmwareVersion());
   }

   /* exit if no board found */
   nBoards = drs->GetNumberOfBoards();
   if (nBoards == 0) {
      printf("No DRS4 evaluation board found\n");
      return 0;
   }

   /* continue working with first board only */
   b = drs->GetBoard(0);

   /* initialize board */
   b->Init();

   /* set sampling frequency */
   b->SetFrequency(1, true);

   /* enable transparent mode - needed for analog trigger */
   b->SetTranspMode(1);

   /* set input range to -0.5V ... +0.5V */
   b->SetInputRange(0);

   /* use following line to set range to 0..1V */
   //b->SetInputRange(0.5);
   
   /* use following line to turn on the internal 100 MHz clock connected to all channels  */
   //b->EnableTcal(1);

   /* use following lines to enable hardware trigger on CH1 at 50 mV positive edge */
   if (b->GetBoardType() >= 8) {        // Evaluaiton Board V4&5
      b->EnableTrigger(1, 0);           // enable hardware trigger
      b->SetTriggerSource(1<<0);        // set CH1 as source
   } else if (b->GetBoardType() == 7) { // Evaluation Board V3
      b->EnableTrigger(0, 1);           // lemo off, analog trigger on
      b->SetTriggerSource(0);           // use CH1 as source
   }

   b->EnableTrigger(1, 0);           // enable hardware trigger
   b->SetTriggerSource(1<<0);        // set CH1 only as trigger 
   b->SetTriggerLevel(-0.02);            // in Volts 
   b->SetTriggerPolarity(false);        // negative-going edge
   b->SetTriggerDelayNs(500);		// get the pulse in the middle of the waveform 

   /* repeat ten times */
   for (j=0 ; j<number_of_events ; j++) {

      /* start board (activate domino wave) */
      b->StartDomino();

      /* wait for trigger */
      // printf("Waiting for trigger...");
      
      fflush(stdout);
      while (b->IsBusy());

      /* read all waveforms */
      b->TransferWaves(0, 8);

      // Loop over all channels
      int ch_div2=0;
	
	/* 	read time (X) array of second channel in ns
       		Note: On the evaluation board input #1 is connected to channel 0 and 1 of
       		get the input #2 we have to read DRS channel #2, not #1. */
	for(int ch=0;ch<8;ch+=2){
	      /* read time (X) array of first channel in ns */
	      b->GetTime(0, ch, b->GetTriggerCell(0), time_array[ch_div2]);

	      /* decode waveform (Y) array of first channel in mV */
	      b->GetWave(0, ch, wave_array[ch_div2]);

	      ch_div2++;
      }
    
	/*
		 In software now - find how many other channels have fired... 
	*/
	// The trigger levels to check for events in the channels (other than 1)
	double trigger_levels[4] = {-20.0,-20.0,-20.0,-20.0};

	// Holds whether the channels have been triggered
	int channels_trg[4];

	// The total number of channels with pulses
	int num_fired_channels=0;

	// Holds the event time relative to the start of the waveform trace	
	double channel_trg_time[4] = {-100.0,-100.0,-100.0,-100.0};
	// The pulse height - if the pulse is negative then this is the minimum voltage value 
	double channel_pulse_height[4] = {100000.0,100000.0,100000.0,100000.0};

	// Loopver of all channels 
	for(int ch=0; ch<4;ch++){
		// Initialize the triggered flag 
		channels_trg[ch] = 0;

			// Loop over the samples
			for(i=0 ; i<1024 ; i++){

			// Look for falling edge of the negative pulse, only trigger in software if it's less than the trigger_levels variable
			if(wave_array[ch][i] < trigger_levels[ch]) {
				// If in here, then the channel has triggered 
	
				// Set the trigger time if this is channel 1  (here this is actually called channel 0)
				if(channels_trg[ch]==0) channel_trg_time[ch] = time_array[ch][i];
			
				// Set the channel triggered flag
				channels_trg[ch] = 1;

				// Increment the count by 1 of how many channels have triggered
				num_fired_channels++;

				// Check if the pulse (negative) peak has been reached 
				if(wave_array[ch][i] < channel_pulse_height[ch]) channel_pulse_height[ch] = wave_array[ch][i];


			}// Triggered if statement end

		}
	}


	// Check for unrealistic coincident pulses -  
	// Variable del_trg_times holds the difference between channel 1 and the others 
	double del_trg_times=0;
	for(int ch=1; ch<4;ch++){
		if(channels_trg[ch]>0) del_trg_times += (double) (channel_trg_time[ch] - channel_trg_time[0]);
	}
	// if(del_trg_times!=0) std::cout << "del t " << del_trg_times << std::endl;

	// This ensures that it is channel 1 and (ch2 OR ch3 OR ch4) and (pulses are coincident within 500ns) and that the pulse
	// in channel 1 in within 200ns of the middle of the waveform
	if((num_fired_channels>1)&&(num_fired_channels<4)&&(fabs(del_trg_times)<500.0)&&(fabs(channel_trg_time[0]-500)<200.0)){

	    	// Get the local timestamp in ms from the computer
	    	struct timeval t;
	    	gettimeofday(&t, NULL);
		long int timestamp = t.tv_sec * 1000 + t.tv_usec / 1000;
		
		// Write out the data to the terminal 
		//	j holds the event number 
		//	Event number // trigger time in channel 0 // Ch. 0 triggered? (1=yes,0=no) // Ch. 1 triggered? 
		// 	Ch. 2 triggered? // Ch. 3 triggered? // Ch. 4 triggered? 
		// 	Trigger times for those channels triggered in order of the channel numbers 
		//	e.g. 
		//		12  1496997758265  502.02  1  0  1  0  502.02  760.20 
		//				where channels 1 and 3 are triggered at times 502.02ns. 
		//					The event time is 1496997758265 and the event number is 2. 

		std::cout << " " << std::left << std::setw(10) << j << " " << std::setw(15) << timestamp << " ";		
		// 
		for(int ch=0; ch<4;ch++){
			std::cout << " " << std::setw(1) << channels_trg[ch];
			if(channels_trg[ch]>0) std::cout << " " << std::left << std::setw(8) << channel_trg_time[ch] << " " << std::left << std::setw(8) << fabs(channel_pulse_height[ch]);
		}
		std::cout << std::endl;
	} else{
		// If the program gets here then there is no coincidence
		j--;
	}
 
  }
  /* delete DRS object -> close USB connection */
   delete drs;
}

