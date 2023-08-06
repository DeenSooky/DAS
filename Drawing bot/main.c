#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include "rs232.h"
#include "serial.h"

#define bdrate 115200               /* 115200 baud */
#define shapes_number 6            //Settting the number of shapes on the file to 6

void SendCommands (char *buffer ); //Funtion 1 used to send the commands to the arduino using the parameter buffer
void Store_Read_ShapeStrokeData(FILE * DataFile, int lineCount); //Function 2 used to store and read the shapestrokeData file with parameters DataFile and lineCount
int LineCount(FILE * DataFile); //Function 3 method to store the file data line  by line 
void DRAW_GRID(char * buffer); //Function 4 used to draw the grid
void Gcode_conversion_transferData(int Xcoordinate, int Ycoordinate, char * Shape_Data, char * buffer); //Function 5 converts the file data to Gcode and transfers the Gcode
int Print_Buffer(char * buffer); //Function 6 used for diagnostic purposes

/* set of Structs */
struct Grid_Coordinates // struct  used to store different types of relatable vairbles 
{
    int x;
    int y;
    int PMode;
};
struct Shape_info
{
    char Shape_name[100];
    int stroke_number;
    struct Grid_Coordinates * pointer; //pointer that points to the the adress of the Grid_coordinates struct
};
struct Shape_info shape_info[shapes_number];

struct Storage_info //Struct to store the file data using varaibles listed within the struct 
{
    
    int Xcoordinate;
    int Ycoordinate;
    char Shape_Data[100];
};

struct Storage_info * Storage_data;


int main()
{
    char buffer[100];
    FILE *DataFile;
    FILE *Draw_shape_Data;

    DataFile = fopen("ShapeStrokeData.txt", "r"); //Opens the shapestrokedata file in read mode and stores it in DataFile
    if (DataFile == NULL )
    {
        printf("Failed to open ShapeStrokeData.txt\n"); //Null will pop up in the terminal if the file is not opened correctly
        return -1; // returns -1 in the case of failure 
    }

    int LineCount_shape = LineCount(DataFile);
    Store_Read_ShapeStrokeData(DataFile, LineCount_shape);
    fclose(DataFile);

    printf("Please enter the name of the drawing instruction file:  ");
    char Draw_shape_Data[100];
    scanf("%s[^\n]%*c", Draw_shape_Data); //Stores the users input file in the string Draw_shape_Data
     Draw_shape_Data = fopen("DrawShapes.txt", "r");
    if (Draw_shape_Data == NULL)
    {
        printf("Failed to open the Draw_shape_Data file\n");
        return -1;
    }
    int instructionLineCount = LineCount(Draw_shape_Data);
    
    // Time to wake up the robot
    printf ("\nAbout to wake up the robot\n");

    // We do this by sending a new-line
    sprintf (buffer, "\n");
    // printf ("Buffer to send: %s", buffer); // For diagnostic purposes only, normally comment out
    Print_Buffer (&buffer[0]);
    Sleep(100);

    printf ("\nThe robot is now ready to draw\n");

    //These commands get the robot into 'ready to draw mode' and need to be sent before any writing commands
    sprintf (buffer, "G1 X0 Y0 F1000\n");
    SendCommands(buffer);
    sprintf (buffer, "M3\n");
    SendCommands(buffer);
    sprintf (buffer, "S0\n");
    SendCommands(buffer);

    // Sending commands to draw the grid
    DRAW_GRID(buffer);
    
    // Sending commands to convert data to gcode and transfer the data
    ReadGcode_conversion_transferDataData(Draw_shape_Data, instructionLineCount, buffer);
 
    // Before we exit the program we need to close the COM port
    Sleep(2000);
    printf("Com port now closed\n");

    //Free up space by removing undesired data
    free(Storage_data);
    for(int i = 0; i < shapes_number; i++)
    {
        free(shape_info[i].pointer);
    }

    return (0);
}

// Send the data to the robot - note in 'PC' mode you need to hit space twice
// as the dummy 'WaitForReply' has a getch() within the function.
void SendCommands (char *buffer )
{
    // printf ("Buffer to send: %s", buffer); // For diagnostic purposes only, normally comment out
    PrintBuffer (&buffer[0]);
    WaitForReply();
    Sleep(100); // Can omit this when using the writing robot but has minimal effect
    // getch(); // Omit this once basic testing with emulator has taken place
}

void Gcode_conversion_transferData(int Xcoordinate, int Ycoordinate, char * Shape_Data, char * buffer)
{
    double XGcode;
    double YGcode;
    int gCodePMode = 0;

    for(int i = 0; i < shapes_number; i++) 
    {
        if(strcmp(shape_info[i].Shape_name, Shape_Data) == 0) //string comparisson function to compare the two strings 
        {
            for(int j = 0; j < shape_info[i].stroke_number; j++) //loops throught the file line by line until the edn is reached
            {
                XGcode = Xcoordinate ;
                YGcode = Ycoordinate; 
                gCodePMode = shape_info[i].pointer[j].PMode; 
                
                if(gCodePMode == 0)
                {
                    sprintf (buffer, "S0\n");
                    SendCommands(buffer);
                }

                sprintf (buffer, "G%d X%.2f Y%.2f\n", gCodePMode, XGcode, YGcode);//alterting the contenets of the file to have the format of gcode
                SendCommands(buffer);
            }
        
        }
    }
}

void Store_Read_ShapeStrokeData(FILE * DataFile, int lineCount)
{
    printf("%d", lineCount);

    for(int i = 0; i < lineCount; i++) //If i is less than the linecount then add 1 to i
    {
       
        if(i == 0)
        {
            fscanf(DataFile, "%s*[^\n]\n");
            continue;
        }
        
        if(i == 2 || i == 9 || i == 15 || i == 27 || i == 33 || i == 48); // i=lines where the the name of the shapes are located in the file
     
    }
}

int LineCount(FILE * DataFile)
{
    int lineCount = 0;
    char character = (char) fgetc(DataFile);
    while (character != EOF)
    {
        
        if (character == '\n') //when \n is shown at the end of the line increase the linecount by one
        {
            lineCount++;
        }
        
        character = (char) fgetc(DataFile); //stores the character next in line
    }

    fseek(DataFile, 0, SEEK_SET); // Will allow you to read to the end of the file 
    return lineCount;
}

void DRAW_GRID(char * buffer)
{
   //Drawing the grid
    sprintf (buffer, "G0 X0 Y0\n"); 
    SendCommands(buffer);
    sprintf (buffer, "S1000\n");                              
    SendCommands(buffer);
    sprintf (buffer, "G1 X90 Y0\n");
    SendCommands(buffer);
    sprintf (buffer, "G1 X90 Y-90\n");
    SendCommands(buffer);
    sprintf (buffer, "G1 X0 Y-90\n");
    SendCommands(buffer);
    sprintf (buffer, "G1 X0 Y0\n");
    SendCommands(buffer);
    sprintf (buffer, "S0\n");
    SendCommands(buffer);
    sprintf (buffer, "G0 X30 Y0\n");
    SendCommands(buffer);
    sprintf (buffer, "S1000\n");
    SendCommands(buffer);
     sprintf (buffer, "G1 X30 Y-90\n");
    SendCommands(buffer);
    sprintf (buffer, "S0\n");
    SendCommands(buffer);
    sprintf (buffer, "G0 X60 Y-90\n");
    SendCommands(buffer);
    sprintf (buffer, "S1000\n");
    SendCommands(buffer);
    sprintf (buffer, "G1 X60 Y0\n");
    SendCommands(buffer);
    sprintf (buffer, "S0\n");
    SendCommands(buffer);
    sprintf (buffer, "G0 X0 Y-30\n");
    SendCommands(buffer);
    sprintf (buffer, "S1000\n");
    SendCommands(buffer);
    sprintf (buffer, "G1 X90 Y-30\n");
    SendCommands(buffer);
     sprintf (buffer, "S0\n");
    SendCommands(buffer);
    sprintf (buffer, "G0 X90 Y-60\n");
    SendCommands(buffer);
    sprintf (buffer, "S1000\n");
    SendCommands(buffer);
    sprintf (buffer, "G1 X0 Y-60\n");
    SendCommands(buffer);
    sprintf (buffer, "S0\n");
    SendCommands(buffer);
    sprintf (buffer, "G0 X0 Y0\n");
    SendCommands(buffer);
}

int Print_Buffer (char *buffer)
{
    //RS232_cputs(cport_nr, buffer);
    printf("%s\n", buffer);

    return (0);
}
