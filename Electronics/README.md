# README

## Electronics Overview

For each detector, we need to count the number of pulses on it that are coincident with others through another one place some distance away. This provides coarse measurement of the cosmic ray track.

There are two approaches to the development of the electronics (that I can think of):

1 Preamp-Discriminator for each channel and then Coincidence-Counter
2 Take all of the detector pulses into a fast digitizer and in the acquisition software, package the event information (time, pulse height, detector numbers hit) into a single event.  

Aside from a number of technical pros and cons the most basic one is: 

Option 1 is cheaper but takes alot of work
Option 2 is expensive but quick

## Requirements

The design must have or do... 

* Approximately 12 channels 
* Sub-20ns timing resolution 
* Low-power where practicable
* Minimize the number of cables to the system
* Setup must be robust over 6 to 12 months
* Enable an understanding (and mitigation) of the environmental dependence of its performance
