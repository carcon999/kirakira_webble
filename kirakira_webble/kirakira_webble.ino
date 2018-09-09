#include <Adafruit_Microbit.h>
#include <Adafruit_NeoPixel.h>

#define BLE_UART_MAX    4
#define LED_COUNT       40
#define LED_PIN         1     // LED出力PIN番号

#define DISP_PAIR_WAIT  0
#define DISP_PAIRING    1
#define DISP_CLEAR      2

static Adafruit_Microbit microbit;
static Adafruit_NeoPixel ledbar = Adafruit_NeoPixel(LED_COUNT);

const uint8_t disp[3][5] ={
  {B11111,B10001,B10001,B10001,B11111}, // □
  {B00000,B01110,B01010,B01110,B00000}, // ㇿ
  {B00000,B00000,B00000,B00000,B00000}, // なし
};

static boolean m_connected = false;
static uint8_t m_buff[BLE_UART_MAX];
static uint8_t m_index;

void disp_draw(uint8_t index)
{
  microbit.matrix.show(&disp[index][0]);
}

void ledbar_draw(uint8_t data[])
{
  for(int i = 0 ; i < data[3]; i++)
  {
    ledbar.setPixelColor(i, data[0], data[1], data[2]);
  }
  for(int i = data[3] ; i < LED_COUNT ; i++)
  {
    ledbar.setPixelColor(i, 0, 0, 0);
  }
  ledbar.show();
}

void ledbar_clear(void)
{
  for(int j = LED_COUNT - 1; j >= 0; j--){
    ledbar.setPixelColor(j, 0, 0, 0);
  }
  ledbar.show();
}
    
void setup(void) 
{
  Serial.begin(115200);
  Serial.println("micro:bit start.");

  // デバイス名の指定
  microbit.BTLESerial.setLocalName("kirakirabit");
  microbit.BTLESerial.begin();

  microbit.matrix.begin();
  disp_draw(DISP_PAIR_WAIT);

  ledbar.setPin(LED_PIN);
  ledbar.updateType(NEO_GRB + NEO_KHZ800);
  ledbar.begin();
}

void loop(void) 
{
  microbit.BTLESerial.poll();

  // 接続中処理
  if(microbit.BTLESerial.connected()){
    if(!m_connected){
      Serial.println("micro:bit connected.");
      m_connected = true;

      disp_draw(DISP_PAIRING);
    }

    // 受信データ読み込み処理（４バイト）
    while(m_index < BLE_UART_MAX && microbit.BTLESerial.available())
    {
      m_buff[m_index] = microbit.BTLESerial.read();
      m_index++;
    }

    // 全データ受信後
    if(m_index == BLE_UART_MAX){
      m_index = 0;

      // LED更新中はチラつくので消灯する。
      disp_draw(DISP_CLEAR);
      
      ledbar_draw(m_buff);

      char buff[32];
      sprintf(buff, "0x%02X 0x%02X 0x%02X 0x%02X\n", m_buff[0], m_buff[1], m_buff[2], m_buff[3]);
      Serial.print(buff);
    }

  // 未接続中処理
  }else{
    if(m_connected){
      ledbar_clear();
      Serial.println("micro:bit disconnected.");
      m_connected = false;

      disp_draw(DISP_PAIR_WAIT);
    }
  }
}
