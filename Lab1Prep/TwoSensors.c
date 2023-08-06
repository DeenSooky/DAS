#include <stdio.h>
#include <math.h>

float NISTdegCtoMilliVoltsKtype(float tempDegC)
/* returns EMF in millivolts */
{
    int i;
    float milliVolts = 0;
    if(tempDegC >= -170 && tempDegC < 0)
    {
        const float coeffs[11] =
        {
            0.000000000000E+00,
            0.394501280250E-01,
            0.236223735980E-04,
            -0.328589067840E-06,
            -0.499048287770E-08,
            -0.675090591730E-10,
            -0.574103274280E-12,
            -0.310888728940E-14,
            -0.104516093650E-16,
            -0.198892668780E-19,
            -0.163226974860E-22
        };
        for (i=0; i<=10; i++)
        {
            milliVolts += coeffs[i] * pow(tempDegC,i);
        }
    }
    else if(tempDegC >= 0 && tempDegC <= 1372)
    {
        const float coeffs[10] =
        {
            -0.176004136860E-01,
            0.389212049750E-01,
            0.185587700320E-04,
            -0.994575928740E-07,
            0.318409457190E-09,
            -0.560728448890E-12,
            0.560750590590E-15,
            -0.320207200030E-18,
            0.971511471520E-22,
            -0.121047212750E-25
        };
        const float a0 =  0.118597600000E+00;
        const float a1 = -0.118343200000E-03;
        const float a2 =  0.126968600000E+03;

        for (i=0; i<=9; i++)
        {
            milliVolts += coeffs[i] * pow(tempDegC,i);
        }

        milliVolts += a0*exp(a1*(tempDegC - a2)*(tempDegC - a2));
    }
    else
    {
        milliVolts = 99E99;
    }
    return milliVolts;
}

float NISTmilliVoltsToDegCKtype(float tcEMFmV)
// returns temperature in deg C.
{

        int i, j;
        float tempDegC = 0;
        const float coeffs[11][3] =
        {
          {0.0000000E+00,  0.000000E+00, -1.318058E+02},
         {2.5173462E+01,  2.508355E+01,  4.830222E+01},
         {-1.1662878E+00,  7.860106E-02, -1.646031E+00},
         {-1.0833638E+00, -2.503131E-01,  5.464731E-02},
         {-8.9773540E-01,  8.315270E-02, -9.650715E-04},
         {-3.7342377E-01, -1.228034E-02,  8.802193E-06},
         {-8.6632643E-02,  9.804036E-04, -3.110810E-08},
         {-1.0450598E-02, -4.413030E-05,  0.000000E+00},
         {-5.1920577E-04,  1.057734E-06,  0.000000E+00},
         {0.0000000E+00, -1.052755E-08,  0.000000E+00}
       };
       if(tcEMFmV >=-5.891 && tcEMFmV <=0 )
       {
           j=0;
       }
       else if (tcEMFmV > 0 && tcEMFmV <=20.644  )
       {
           j=1;
       }
       else if (tcEMFmV > 20.644 && tcEMFmV <=54.886  )
       {
           j=2;
       }
       else
       {
           return 99E9;
       }

       for (i=0; i<=9; i++)
        {
            tempDegC += coeffs[i][j] * pow(tcEMFmV,i);
        }
    return tempDegC;
}

/* Write a function here to convert ADC value to voltages. (Part a, equation 1)
Call it from the main() function below */
float ADCtoVol (int nADC, float VRef) //Creating the function ADCtoVol, using variables nADC and Vref whilst storing it as a float 
{
    float VADC = ((nADC*VRef)/1024); //Eq(1) logic
    return VADC; //returning the variable VADC so that the function takes this variables value

}
// Write a function to convert degrees K to degrees C  (Part b, (iv))
float KeltoDeg(float tempresult, float DegConversion) //Creating the function KeltoDeg, using variables tempresult and DegConversion whilst storing it as a float 
{
    float TempDeg = (tempresult - DegConversion); // conversion equation from kelvins to degrees
    return TempDeg; //returning the variable TempDeg so that the function takes this variables value
}

//Call it from the main() function below */

int main()
{
    // Define VRef
    float VRef = 5.00; // Storing the value 5 into VRef as a float 
     
    // Define Thermistor constants
    float DegConversion = 273.15;
    float To = 298.15;
    float B = 3975;
    float Ro = 10;
    
    // User input for one pin value to test all outputs
    
    int nADC = 0; //Storing the value 0 into nADC as a integer
    printf("ADC value:"); //Print statement asking for nADC input from user
    scanf("%d", &nADC); //Input function to store inputed valued into nADC as a integer from user
    float VADC = ADCtoVol(nADC, VRef); //calling the function ADCtoVol using varibales nADC and VRef

    // Calculate thermistor temperature in degrees C ( Part b, i,ii,iii & v)
     
     float ResThermS = ((10*3.3)/VADC)-10; //Eq(4) logic to convert the voltage from the ADC to its corresponding resistance value 
     float REStoTemp = (1/To+1/B*log(ResThermS/Ro)); //Eq(3) logic converting reistance to its corresponding temperature
     int exp = -1; //Storing the exponential as -1
     float tempresult = pow(REStoTemp,exp); //Power function in the from of pow(base,exponential)
     float TempDeg = KeltoDeg(tempresult,DegConversion); //calling the function KeltoDeg using varibales tempresult and DegConversion
     // Output result
     printf("Thermistor temperature (deg C): %.2f\n", TempDeg); //Displaying the output for the temperature of the thermistor with a precision of 2 decimal places

    // Calculate thermocouple temperature in degrees C ( Part c, i - iv)
    float PreThermoCoupleVol = (VADC-0.35)/54.4; //Eq(5) logic converting ADC voltage to thermocouple voltage
    float tempDegC = TempDeg; //Storing Temperature of thermistor in degrees into the varibale used in the Forward function
    float ForwardFunction = NISTdegCtoMilliVoltsKtype(tempDegC);//calling the function NISTdegCtoMilliVoltsKtype using varibales tempDegC
    float tcEMFmV = (PreThermoCoupleVol*pow(10,3)) + ForwardFunction;//Eq(6) logic where PreThermoCoupleVol is converted to mV
    float InverseFunction = NISTmilliVoltsToDegCKtype(tcEMFmV);//calling the function NISTmilliVoltsToDegCKtype using varibales tcEMFmV
    // Output result
    printf("Thermocouple temperature with CJC (deg C): %.2f \n", InverseFunction); //Displaying the output for the temperature of the thermocpuple with a precision of 2 decimal places
    

    return 0;
}
