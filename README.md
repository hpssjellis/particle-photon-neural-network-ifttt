# particle-photon-neural-network-ifttt
Just playing around with the Neural Networks and the particle photon with IFTTT and possibly TensorFlow




Dec 15, 2015


Need at least three photons to teswt this out but should have 17 photons for full trial, this should be able to be extended to many photons.


Entry.ino takes a set of 8 bits from a google doc using IFTTT and sends the information to the main layer of 8 photons

Layer.ino on each photon in the main layer receives the data using an analog channel, if greater than a set amount sends data to other photons. and distributes to 8 other photons


exit.ino  the last eight photons which send their data through IFTTT to another google Docs


Learning. If the exit photon(s) are correct IFTTT sends a reward (???) to the main layers. If no reward the main layers randomnize the outputs to their next layers


On the photon the only pins used are:

A0 = receive inputs
D0-D7 send outputs to specific photons. This line will need a resistor, I will try 100 Ohm's to start with and see if the range is OK for the Analog read 0 - 4095
