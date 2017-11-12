/* TPIC6C595N shift register (drain type) implimentation 
Start filling the array starting at DRAIN 7 corresponding to the first spot in the array*/

//It should be that 0 corresponds to Drain 0, as in the end of the array gets sent in first

#define SER_IN    2
#define G_        3
#define RCK       4
#define SRCK      5
//#define CLR       6 hook up to power

void setup() {
  pinMode(G_, OUTPUT);
  pinMode(RCK, OUTPUT);
  pinMode(SER_IN, OUTPUT);
  pinMode(SRCK, OUTPUT);
  Serial.begin(115200);
  digitalWrite(RCK, LOW);       // Latch, not latching
  digitalWrite(G_, HIGH);       // Output not enabled
  digitalWrite(SER_IN, LOW);    // no data
  digitalWrite(SRCK, LOW);      // no clock pulse
  }

void loop() {
  int size_arr = 8*4;
  int * head = new int[size_arr];
    turn_off(head, size_arr);
  /*
   * LEDs:1: 5,6 see journal pg July 19th
   *      2: 2
   *      3: 0
   *      4: 4
   */
//   head[5] = 1;
//   head[6] = 1;
//   head[10] = 1;
   head[18] = 1;
   head[31] = 1;
  send_data(head, size_arr);
}

/* Reads serial input on rising edge of clock 
Sends the end of the array in first, arr[7] = DRAIN 7 
Verified to be accurate
*/
void send_data(int * data, int num_items)
{
  digitalWrite(G_, HIGH);             // output not enabled
  for (int i = num_items-1; i >= 0; i--)
  {
    digitalWrite(SRCK, LOW);
    if(data[i])
    {
       digitalWrite(SER_IN, HIGH);
    }
    else
    {
      digitalWrite(SER_IN, LOW);
    }
    digitalWrite(SRCK, HIGH);
  }
  digitalWrite(SRCK, LOW);
  digitalWrite(RCK, HIGH);
  delay(1);
  digitalWrite(RCK, LOW);
  digitalWrite(G_, LOW);
}

void turn_off(int * head, int old_size)
{
  for (int i = 0; i < old_size; i++)
    head[i] = 0;
}

void turn_on(int * head, int old_size)
{
  for (int i = 0; i < old_size; i++)
    head[i] = 1;
}

