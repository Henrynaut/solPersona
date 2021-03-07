#include <dht_nonblocking.h>
#include <SoftwareSerial.h>
#define DHT_SENSOR_TYPE DHT_TYPE_11

SoftwareSerial mySerial(0, 0);

static const int DHT_SENSOR_PIN = 4;
DHT_nonblocking dht_sensor( DHT_SENSOR_PIN, DHT_SENSOR_TYPE );

void setup( )
{
  Serial.begin( 9600);
  mySerial.begin(38400);
}
void loop( )
{
  float temperature;
  float humidity;
  if(dht_sensor.measure(&temperature, &humidity)){
    Serial.print( "T = " );
    Serial.print ( temperature, 0);
    Serial.print( " deg. C, H = " );
    Serial.print( humidity, 1 );
    Serial.println( "%" );
  }
    
    mySerial.write(humidity);
}
