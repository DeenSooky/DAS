#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define bool int
#define byte unsigned char
#define numChars  32

void initialiseEncoderStateMachine();
void updateEncoderStateMachine();

// Here we are using global variables simply to be compatible with the Arduino program structure
// This is REALLY bad practice so please don't do it otherwise!
long int count = 0;
long int error = 0;

enum states {state1=1, state2, state3, state4};
bool channelAState=0;
bool channelBState=0;

enum states state;
char receivedChars[numChars]="00";   // an array to store the received data

int main()
{
    // Replicates the setup in Arduino
    printf("Enter a pair of characters representing initial states of channels A and B\n");
    scanf("%s",receivedChars);
    channelAState = receivedChars[0]!='0';
    channelBState = receivedChars[1]!='0';

    initialiseEncoderStateMachine();
    printf("State %d, count %ld, error %ld\n", state, count, error);
    printf("Enter a pair of characters representing channels A and B, enter 99 to end\n");

    // Replicates the loop in Arduino
    do
    {
        scanf("%s",receivedChars);
        if (strcmp(receivedChars, "99")==0)
        {
            break;
        }
        channelAState = receivedChars[0]!='0';
        channelBState = receivedChars[1]!='0';
        updateEncoderStateMachine();
        printf("State %d, count %ld, error %ld\n", state, count, error);

    }
    while(1);
    return 0;
}
void initialiseEncoderStateMachine()
{
    /* If initially A is 0 and B is 0, system starts in State 1
       If initially A is 1 and B is 0, system starts in State 2
       If initially A is 1 and B is 1, system starts in State 3
       If initially A is 0 and B is 1, system starts in State 4 */

    if (channelAState) // if statement with condition channelAState set at 1
    {
        if(channelBState) // sub if statement with condition channelBStatement set at 1
        {
            state = state3; // if both channelBStatement and channelAStatement are 1 then this line of code will be excuted, state will be set to state3
        }
        /* else ....  lots of code goes here */
        else // else statement refering to if channelBStatement is 0
        {
            state=state2; // if channelBStatement is 0 and channelAStatement is 1 then this line of code will be excuted, state will be set to state2

        }
    }
    if (!channelAState) // if statement with condition channelAState set at 0
    {
        if(channelBState) 
        {
            state = state4; // if channelBStatement is 1 and channelAStatement is 0 then this line of code will be excuted, state will be set to state4
        }
        else
        {
            state = state1; // if channelBStatement is 1 and channelAStatement is 1 then this line of code will be excuted, state will be set to state1

        }
    }
    
}

void updateEncoderStateMachine()
{
    if ( !channelAState && !channelBState) // if statement with conditoins channelAState is 0 and channelBState is 0
    state =state1; // if above statement is met then state will be set to state1
    else if (channelAState && channelBState)
    state =state3;
    else if (!channelAState && channelBState) // if statement with conditoins channelAState is 0 and channelBState is 1
    state =state4; // if above statement is met then state will be set to state4
    else if (channelAState && !channelBState)
    state =state2;
    switch (state)
    {
    case state1: // case state1 refers to state1 mentioned above, if state1 conditons are met then code below is excuted, state is set to state 1
        /* If A is 0 and B is 0, do nothing and stay in State 1
           If A is 1 and B is 0, add 1 to main counter and go to State 2
           If A is 0 and B is 1, subtract 1 to main counter and go to State 4
           If A is 1 and B is 1, do nothing to main counter but add 1 to error counter and go to state 3 */

        state=state1;
        break; //Stops the rest of the code below from being reading if case state1 is met
        /* else ....  lots of code goes here */
        case state2:
        count++; //count increases by 1
        state=state2; 
        break;
        case state3: // case state3 refers to state3 mentioned above, if state3 conditons are met then code below is excuted, state is set to state3 and erro increases by 1
        error++; //error increases by 1
        state=state3;
        break;
        case state4:
        count--; // count decreases by 1
        state=state4;
        break;
    }
}
