#define a0_lpf 0.007992
#define a1_lpf 0.01598
#define a2_lpf 0.007992
#define b1_lpf -1.642
#define b2_lpf 0.6744
#define a0_hpf 0.8292
#define a1_hpf -1.658
#define a2_hpf 0.8292
#define b1_hpf -1.642
#define b2_hpf 0.6744

#define SET_OUTPUT_A 0x1000
#define SET_OUTPUT_B 0x1000

float t = 0;
int n = 2;
int ADC = 1;
float input[3] = {0, 0, 0};
float output_low[3] = {0, 0, 0};
float output_high[3] = {0, 0, 0};

void setup() {
  // put your setup code here, to run once:
  pinMode(53, OUTPUT);
  SPI.begin();
  Serial.begin(9600);
}

void loop() {
	// put your main code here, to run repeatedly:
	input[n] = analogRead(ADC);
	output_low[n] = -(b2_lpf*output_low[n-2] + b1_lpf*output_low[n-1]) + (a2_lpf*input[n-2] + a1_lpf*input[n-1] + a0_lpf*input[n]);
	output_high[n] = -(b2_hpf*output_high[n-2] + b1_hpf*output_high[n-1]) + (a2_hpf*input[n-2] + a1_hpf*input[n-1] + a0_hpf*input[n]);
	
	input[n-2] = input[n-1];
	output_high[n-2] = output_high[n-1];
  output_low[n-2] = output_low[n-1];
	input[n-1] = input[n];
	output_high[n-1] = output_high[n];
  output_low[n-1] = output_low[n];

  SPI.beginTransaction(SPISettings(20000000, MSBFIRST, SPI_MODE0));
  digitalWrite(53, LOW);
  SPI.transfer16(SET_OUTPUT_A | (1000 + round(1000*output_low[n]));
  digitalWrite(53, HIGH);

  SPI.beginTransaction(SPISettings(20000000, MSBFIRST, SPI_MODE0));
  digitalWrite(53, LOW);
  SPI.transfer16(SET_OUTPUT_B | (1000 + round(1000*output_high[n]));
  digitalWrite(53, HIGH);
  
  //print to an output here
	delayMicroseconds(12.5);
}
