# particle-photon-neural-network-ifttt
Just playing around with Neural Networks and the particle photon with IFTTT and possibly TensorFlow

The basic flow of things is to go from serial to digital to analog (summing inputs) back to digital (repeat as needed) then output as serial.

Dec 17, 2015
Afternoon

So..... backpropogation will not work since this Neural Network does not have weights. Each of the 8 connections are digital not analog. This brings up a few points. 

1. Can a software based neural network pre-learn and calculate the connections for this network?
2. While learning can different nodes oscillates at a fixed frequency for that node to see if any effect is produced on the final nodes. This oscillation frequency could then be used to determince which node is causing the positive change and solidify that node to that positive effect.


Dec 17, 2015
Morning

Found a really good site to explain Back Propagation at 

http://mattmazur.com/2015/03/17/a-step-by-step-backpropagation-example/

Which shows an issue with my Photon Neural Network. I am using Digital Output pins which can't be set as having weights. If I had 8 analog outputs I might be able to do backpropagation but I don't. (Analog outputs running PWM might really mess things up. I am waiting for the Particle.io Photon to get DAC outputs working, but it only has two DAC pins A6 and A3)



Dec 16, 2015

I have combined everything into the layer02.ino so entryNodes, NormalNodes and EndNodes can all have the same .ino code flashed to the Photon. Each photon will need a unique number set in the variable "myUniqueNodeNumber". Each photon will also have to define the variable "myType" as either EntryNode, NormalNode or EndNode.


Entry Nodes will have to be the first ones and are activated by a DO IFTTT receipe that passes a bit signal example for 3 entry nodes turning the first and last on would pass 101 to the published event "my-EntryNode". Presetnly this event is private, but I will have to make it public eventually unless all my Photon's are on the same login.

Still have to do the EndNode and figure out backPropogation.



It looks like each layer will have no maximum number of photons, and no maximum number of layers BUT, each photon will only be able to communicate with 8 other photons. (That is the limit of interconnections based on using the Photon)




I also publish using IFTTT DO statements the xFire event (also private but will have to be public eventually). example data sent
G-654    Says the settings are good and the firelimit is 654
B-3000  Says the network has not yet found a good fit so randomize the nodes. also sets the fireLimit very high. Maximum = 4095 Analog read channel.




Dec 15, 2015

layer01.ino is working
started layer02.ino as the new main file. Will try to combine the other node types all in one .ino


Dec 14, 2015


Need at least three photons to test this out but should have 17 photons for full trial, this should be able to be extended to many more photons.


Entry.ino takes a set of 8 bits from a google doc using IFTTT and sends the information to the main layer of 8 photons

Layer.ino on each photon in the main layer receives the data using an analog channel, if greater than a set amount sends data to other photons. and distributes to 8 other photons


exit.ino  the last eight photons which send their data through IFTTT to another google Docs


Learning. If the exit photon(s) are correct IFTTT sends a reward (???) to the main layers. If no reward the main layers randomnize the outputs to their next layers


On the photon the only pins used are:

A0 = receive inputs
D0-D7 send outputs to specific photons. This line will need a resistor, I will try 100 Ohm's to start with and see if the range is OK for the Analog read 0 - 4095
