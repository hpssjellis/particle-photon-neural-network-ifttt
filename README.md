# particle-photon-neural-network-ifttt
Just playing around with Neural Networks and the particle photon with IFTTT and possibly TensorFlow

Dec 17, 2015

I have combined everything into the layer02.ino so entryNodes, NormalNodes and EndNodes can all have the same .ino code flashed to the Photon. Each photon will need a unique number set in the variable "myUniqueNodeNumber". Each photon will also have to define the variable "myType" as either EntryNode, NormalNode or EndNode.


Entry Nodes will have to be the first ones and are activated by a DO IFTTT receipe that passes a bit signal example for 3 entry nodes turning the first and last on would pass 101 to the published event "my-EntryNode". Presetnly this event is private, but I will have to make it public eventually unless all my Photon's are on the same login.

Still have to do the EndNode and figure out backPropagation.



It looks like each layer will have no maximum number of photons, and no maximum number of layers BUT, each photon will only be able to communicate with 8 other photons. (That is the limit of interconnections based on using the Photon)


Dec16, 2015

layer01.ino is working
started layer02.ino as the new main file. Will try to combine the other node types all in one .ino


Dec 15, 2015


Need at least three photons to teswt this out but should have 17 photons for full trial, this should be able to be extended to many photons.


Entry.ino takes a set of 8 bits from a google doc using IFTTT and sends the information to the main layer of 8 photons

Layer.ino on each photon in the main layer receives the data using an analog channel, if greater than a set amount sends data to other photons. and distributes to 8 other photons


exit.ino  the last eight photons which send their data through IFTTT to another google Docs


Learning. If the exit photon(s) are correct IFTTT sends a reward (???) to the main layers. If no reward the main layers randomnize the outputs to their next layers


On the photon the only pins used are:

A0 = receive inputs
D0-D7 send outputs to specific photons. This line will need a resistor, I will try 100 Ohm's to start with and see if the range is OK for the Analog read 0 - 4095
