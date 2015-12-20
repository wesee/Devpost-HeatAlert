# Devpost-HeatAlert
##HeatAlert

## Inspiration
For some reason, you want to monitor the temperature of a venue and to be alerted if the temperature exceeds certain threshold so that you can take some actions to adjust the temperature.


## What it does
I built the HeatAlert system which I can monitor the temperature of a venue.  If the temperate exceeds 28 degree Celsius, the system will call me to inform me of such a situation.  I will decide if I want to turn on air-cond by pressing 1 or ignore the situation by pressing 0 (zero).  The current system uses LED as a metaphor for the air-cond.


## How I built it
I built the system using TI Launchpad CC3200 to read the temperature sensor's (TM35DZ) values.  With Temboo and Nexmo services, if the temperature exceeds 28 degree Celsius the system converts text to speech and makes phone calls to a user and receives a pin-code from the user.  Based on the code, the system will turn on an air-cond or just ignore the situation.


## Challenges I ran into
I ran into the problem of getting the correct temperature from the temperature sensor which is TM35DZ.  I have spent a lot of time trying to get the reasonable formula of converting voltage to degree Celsius.  Most of the answers from internet are for Arduino board which do not give the correct values for Launchpad board.  Eventually I come up with a formula which give reasonable temperature conversion.


## Accomplishments that I'm proud of
I managed to build the system using TI Launchpad CC3200, integrating with third party services like Temboo and Nexmo.

## What I learned
I learned how to setup Nexmo and use Temboo's Nexmo library to convert text to speech and make phone calls to a user and receive a pin-code from the user.


## What's next for HeatAlert
The next for HeatAlert will be (1) adding different sensors and (2) making it a functional home monitoring and control system which actually interacts with appliances like air-conds and lights.



