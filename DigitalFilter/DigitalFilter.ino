#define a0_lpf 0.005303
#define a1_lpf 0.01061
#define a2_lpf 0.005303
#define b1_lpf -1.709
#define b2_lpf 0.7299
#define a0_hpf 0.739018
#define a1_hpf -2.95607
#define a2_hpf 4.43411
#define a3_hpf -2.95607
#define a4_hpf 0.739018
#define b1_hpf -3.41744
#define b2_hpf 4.37958
#define b3_hpf -2.49449
#define b4_hpf 0.532797

float t = 0;
float input[5] = {0, 0, 0, 0, 0};
float output_low[3] = {0, 0, 0};
float output_high[5] = {0, 0, 0, 0, 0};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
}

void loop() {
	// put your main code here, to run repeatedly:
	t += .0000125;
	input[4] = sin(2*PI*100*t)+sin(2*PI*10000*t);
	
	//output_low[2] = -(b2_lpf*output_low[0] + b1_lpf*output_low[1]) + (a2_lpf*input[2] + a1_lpf*input[1] + a0_lpf*input[0]);
	output_high[4] = -(b4_hpf*output_high[0] + b3_hpf*output_high[1] + b2_hpf*output_high[2] + b1_hpf*output_high[3]) + (a4_hpf*input[4] + a3_hpf*input[3] + a2_hpf*input[2] + a1_hpf*input[1] + a0_hpf*input[0]);
	
	input[0] = input[1];
	output_high[0] = output_high[1];
	input[1] = input[2];
	output_high[1] = output_high[2];
  input[2] = input[3];
  output_high[2] = output_high[3];
  input[3] = input[4];
  output_high[3] = output_high[4];
  
	//Serial.print(input[2]);
	//Serial.print(" ");
	//Serial.print(output_low[2]);
	//Serial.print(" ");
	Serial.println(output_high[4]);
	delayMicroseconds(12.5);
}
