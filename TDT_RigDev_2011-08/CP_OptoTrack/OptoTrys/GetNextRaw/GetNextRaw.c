#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

#include "ndhost.h"
#include "ndtypes.h"
#include "ndpack.h"
#include "ndopto.h"

#define NUM_SENSORS 3
#define NUM_MARKERS 10
#define N_FRM_BLOCK 1000
#define N_FRAMES    5000

/*****************************************************************
Static Structures and Types:
*****************************************************************/

/*
 * Typedef for sensor data returned in a full raw data packet.
 */
typedef struct SensorDataStruct
{
    unsigned char   ucPeak;
    unsigned char   ucDRC;
    unsigned char   ucCode;
    unsigned char   ucPeakNibble;
} SensorDataType;


/*
 * Typedef for a full raw data packet.
 */
typedef struct FullRawDataStruct
{
    float           fCentroid[ NUM_SENSORS];
    SensorDataType  SensorData[ NUM_SENSORS];
} FullRawDataType;

/*****************************************************************
Global Variables:
*****************************************************************/

/*
 * Array of strings for the sensor status codes.
 */
static char
    *pSensorStatusString[ 9] =
    {
        "CENTROID_OK",
        "CENTROID_WAVEFORM_TOO_WIDE",
        "CENTROID_PEAK_TOO_SMALL",
        "CENTROID_PEAK_TOO_LARGE",
        "CENTROID_WAVEFORM_OFF_DEVICE",
        "CENTROID_FELL_BEHIND",
        "CENTROID_LAST_CENTROID_BAD",
        "CENTROID_BUFFER_OVERFLOW",
        "CENTROID_MISSED_CCD"
    };

//*****************************************************************
void main( int argc, unsigned char *argv[] ){
  int
    nNumSensors,
    nNumOdaus,
    nMarkers,
    nSensorCode;
  unsigned int
    uFlags,
    uElements,
    uFrameCnt,
    uMarkerCnt,
    uSensorCnt,
    uFrameNumber,
    uSpoolStatus = 0;
  static FullRawDataType
    pFullRawData[ NUM_MARKERS];
  char
    szNDErrorString[MAX_ERROR_STRING_LENGTH + 1];

  unsigned int
    uPrevFrame;
  int nFrames;

    
    // Load the system of transputers.
    if( TransputerLoadSystem( "system" ) )  {
      goto ERROR_EXIT;
    }

    Sleep( 1000 ); // Wait one second to let the system finish loading.

    // Initialize the transputer system.
    if( TransputerInitializeSystem( OPTO_LOG_ERRORS_FLAG )) {
      goto ERROR_EXIT;
    }

    // Set optional processing flags (this overides the settings in OPTOTRAK.INI).
    if( OptotrakSetProcessingFlags( 
//                                    OPTO_LIB_POLL_REAL_DATA |  // if this flag is set, CPU clocks are waisted
                                    OPTO_CONVERT_ON_HOST |
                                    OPTO_RIGID_ON_HOST ) ) {
      goto ERROR_EXIT;
    } 

    // Load the standard camera parameters.
    if( OptotrakLoadCameraParameters( "standard" ) ) {
      goto ERROR_EXIT;
    } 

    // Set up a collection for the OPTOTRAK.
    if( OptotrakSetupCollection(
            NUM_MARKERS,    /* Number of markers in the collection. */
            (float)50.0,   /* Frequency to collect data frames at. */
            (float)1000.0,  /* Marker frequency for marker maximum on-time. */
            30,             /* Dynamic or Static Threshold value to use. */
            160,            /* Minimum gain code amplification to use. */
            0,              /* Stream mode for the data buffers. */
            (float)0.4,    /* Marker Duty Cycle to use. */
            (float)5.0,     /* Voltage to use when turning on markers. */
            (float)1.0,     /* Number of seconds of data to collect. */
            (float)0.0,     /* Number of seconds to pre-trigger data by. */
            OPTOTRAK_BUFFER_RAW_FLAG 
//            | OPTOTRAK_GET_NEXT_FRAME_FLAG 
            
            ) )
    {
        goto ERROR_EXIT;
    } 

    Sleep( 1000 );

/*
    // Request and receive the OPTOTRAK status.
    if( OptotrakGetStatus(
            &nNumSensors,    // Number of sensors in the OPTOTRAK system. 
            &nNumOdaus,      // Number of ODAUs in the OPTOTRAK system. 
            NULL,            // Number of rigid bodies being tracked by the O/T. 
            &nMarkers,       // Number of markers in the collection. 
            NULL,            // Frequency that data frames are being collected. 
            NULL,            // Marker firing frequency. 
            NULL,            // Dynamic or Static Threshold value being used. 
            NULL,            // Minimum gain code amplification being used. 
            NULL,            // Stream mode indication for the data buffers 
            NULL,            // Marker Duty Cycle being used. 
            NULL,            // Voltage being used when turning on markers. 
            NULL,            // Number of seconds data is being collected. 
            NULL,            // Number of seconds data is being pre-triggered. 
            NULL ) )         // Configuration flags. 
    {
      goto ERROR_EXIT;
    }

     // Display elements of the status received.
    printf("Sensors in system       :%3d\n", nNumSensors );
    printf("ODAUs in system         :%3d\n", nNumOdaus );
    printf("Default OPTOTRAK Markers:%3d\n", nMarkers );

    // Activate the markers.
    if( OptotrakActivateMarkers() ) {
        goto ERROR_EXIT;
    }

    
*/
    uPrevFrame = 0;
    // Get and display ten frames of full raw data.
    for( uFrameCnt = 0; uFrameCnt < N_FRAMES; ++uFrameCnt ) {
      // Get a frame of data.
	  // we did set OPTOTRAK_GET_NEXT_FRAME_FLAG, so we will have
      // no repeating frames

      if( (uFrameCnt % N_FRM_BLOCK ) == 0){
        if( uFrameCnt % (N_FRM_BLOCK * 2) == 0)  
          OptotrakActivateMarkers();
        else 
          OptotrakDeActivateMarkers();
      }

      if( DataGetNextRaw( &uFrameNumber, &uElements, &uFlags,
                            pFullRawData ) ){
          goto ERROR_EXIT;
      }
      printf("Frame Number: %8u\r", uFrameNumber );
      nFrames = uFrameNumber - uPrevFrame; 
      if( nFrames > 1 ){
        printf("\nMissed N frames: %d \n", nFrames - 1 );
      }
      
      uPrevFrame = uFrameNumber;
/*
      printf("Frame Number: %8u\n", uFrameNumber );
      printf("Elements    : %8u\n", uElements );
      printf("Flags       : 0x%04x\n", uFlags );

      for( uMarkerCnt = 0; uMarkerCnt < NUM_MARKERS; ++uMarkerCnt ) {

        printf("Marker %u\t\tCentroid Peak  DRC Code\n",  uMarkerCnt + 1 );

        for( uSensorCnt = 0; uSensorCnt < NUM_SENSORS; ++uSensorCnt ){

            printf("\tSensor %u\t", uSensorCnt + 1 );

            if( pFullRawData[ uMarkerCnt].fCentroid[ uSensorCnt] < MAX_NEGATIVE ) {
              printf(" missing " );
            } 
            else {
                printf("%8.2f ",  pFullRawData[ uMarkerCnt].fCentroid[ uSensorCnt] );
            } 

            nSensorCode = pFullRawData[ uMarkerCnt].SensorData[ uSensorCnt].ucCode;
            printf("%4d %4d %s\n",
                pFullRawData[ uMarkerCnt].SensorData[ uSensorCnt].ucPeak,
                pFullRawData[ uMarkerCnt].SensorData[ uSensorCnt].ucDRC,
                pSensorStatusString[ nSensorCode] );
          } // for uMarkerCnt
      } // for uMarkerCnt
*/

      if( uFrameNumber >= N_FRAMES ) break;
  } // for uFrameCnt


/*
    // De-activate the markers.
    if( OptotrakDeActivateMarkers() ) {
        goto ERROR_EXIT;
    } 
*/    
    // Shutdown the transputer message passing system.
    if( TransputerShutdownSystem() ) {
        goto ERROR_EXIT;
    } 

    printf( "\nProgram execution complete.\n" );
    return;

ERROR_EXIT:
    if( OptotrakGetErrorString( szNDErrorString,
                                MAX_ERROR_STRING_LENGTH + 1 ) == 0 ) {
      printf( "\n\nError!\n");
      printf( szNDErrorString );
    } 
    TransputerShutdownSystem();
    return;
} // main 

