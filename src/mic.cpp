#include <mic.h>

#define ADC_OUT 1

bool mic_flag = 0;

String voice_text;
String voice_answer;
String voice_get;
// String token = "24.581e5a0e7b6dfc03dc8d12a14e76827e.2592000.1727168373.282335-110515010";
String token = "24.776a2384a4388f549d33c82d1625b16a.2592000.1735718457.282335-113434065";

const int recordTimeSeconds = 4; // 定时器录音时间 4s
hw_timer_t *timer = NULL;
void IRAM_ATTR onTimer(); // 中断

const int adc_data_len = 16000 * recordTimeSeconds;
uint16_t *adc_data;
const int data_json_len = adc_data_len * 2 * 1.4;
char *data_json;
String data_json2;

uint32_t num = 0;
bool adc_start_flag = 0; // 开始标志
bool adc_read_flag = 0;
bool adc_complete_flag = 0; // 完成标志

// 百度STT API设置
// const char *API_KEY = "88dxgc4v4mbmZDWO9aejcxi5";
// const char *SECRET_KEY = "Hx2TpilDl6Fio9B6Z38i0WrbtMToG4zh";
// const char *ID = "110515010";
// 没用上，获取token
const char *API_KEY = "10OMmaPF5aGYQLPgCxI2VFU4";
const char *SECRET_KEY = "CEPmT8Qaqb7F90hsJ7qdp0VTi1CVWdqO";
const char *ID = "113434065";

// MINIMAX，没用上
String GroupKey = (String) "Bearer " + "eyJhbGciOiJSUzI1NiIsInR5cCI6IkpXVCJ9.eyJHcm91cE5hbWUiOiLovrDlsbEiLCJVc2VyTmFtZSI6Iui-sOWxsSIsIkFjY291bnQiOiIiLCJTdWJqZWN0SUQiOiIxODEwNTQxMzM2MTEwMDU2MzMyIiwiUGhvbmUiOiIxODkyNzA4MzMzOSIsIkdyb3VwSUQiOiIxODEwNTQxMzM2MTAxNjY3NzI0IiwiUGFnZU5hbWUiOiIiLCJNYWlsIjoiIiwiQ3JlYXRlVGltZSI6IjIwMjQtMDgtMjUgMTc6MjI6MzUiLCJpc3MiOiJtaW5pbWF4In0.d74ko6g0fu4hRkIlaj6qPK0ZgkZH-38c2WF3_tlz2L1PHoGB8RBFcjBDiB5X93XxBOdv2cUNFMM3AV20R-npXmPFZp7-OBtPixZvplL4jO3J1h3cRhKpOb8GRPUZQzj6gYosbuzQtjAvoAgcbHZrWiMPHP9sK5qfLVxX2GGecV3-QutU8jXW-MZ8BU91jvfthTcvdzBzeYcYNIXSE66Kkq6zjY1hAU0qy86k8C7fe7BEDRGwUiMO6sBVxLF4Sps3TAtoEX4q8oeAJCr7U1zRzD1NPBFRIBRHZ1q931Ngngp-O6CvDrf8DiVt3Waeiq4BiLAE6BPQFPkE2A2HtH4ZFQ";
String GroupID = "1810541336101667724";

void initmic(void)
{
    pinMode(ADC_OUT, ANALOG);

    adc_data = (uint16_t *)ps_malloc(adc_data_len * sizeof(uint16_t)); // 使用片外PSRAM
    if (!adc_data)
        Serial.println("Failed to allocate memory for adc_data");

    data_json = (char *)ps_malloc(data_json_len * sizeof(char));
    if (!data_json)
        Serial.println("Failed to allocate memory for data_json");

    timer = timerBegin(1, 40, true);   //  80M的时钟 40分频 1M
    timerAlarmWrite(timer, 125, true); //  1M  计125个数进中断  16K
    timerAttachInterrupt(timer, &onTimer, true);
    timerAlarmEnable(timer);
    timerStop(timer); // 先暂停
}

void getmic(void)
{
    if (mic_flag)
    {
        Serial.println("Start");
        audio.stopSong();
        vTaskDelay(100);

        // 设置录音标志和启动定时器
        adc_start_flag = 1;
        timerStart(timer);

        // 监听4s,由中断函数onTimer处理
        while (!adc_complete_flag)
        {
            vTaskDelay(100);
        }

        if (adc_complete_flag)
        {
            timerStop(timer);

            if (!mic_move_flag)
            {
                lv_textarea_set_text(ui_TextAreaQuestion, "请等待...");
            }
            Serial.println("Over");

            aseembleJson(token);
            // 语音信号使用百度STT转为文字，根据mic_move_flag判断是给action赋值还是发送问题给GPT
            sendToSTT();

            if (mic_move_flag)
            {
                lv_textarea_set_text(ui_TextCommand, voice_text.c_str());
                lv_obj_clear_state(ui_SwitchSpeak2, LV_STATE_CHECKED | LV_STATE_DISABLED);
                lv_label_set_text(ui_LabelGPTSwitch2, "OFF");
            }
            else
            {
                lv_textarea_set_text(ui_TextAreaQuestion, voice_text.c_str());
                lv_textarea_set_text(ui_TextAreaAnswer, voice_answer.c_str());
                lv_obj_clear_state(ui_SwitchSpeak, LV_STATE_CHECKED | LV_STATE_DISABLED);
                lv_label_set_text(ui_LabelGPTSwitch, "OFF");
            }

            adc_complete_flag = 0;
            mic_flag = 0;
        }
    }
}

void sendToSTT(void) // 上传到百度云
{
    HTTPClient http_text;
    http_text.begin("http://vop.baidu.com/server_api");
    http_text.addHeader("Content-Type", "application/json");

    int httpCode = http_text.POST(data_json);

    if (httpCode > 0)
    {
        if (httpCode == HTTP_CODE_OK)
        {
            String payload = http_text.getString();
            DynamicJsonDocument doc(1024);
            deserializeJson(doc, payload);
            voice_text = doc["result"].as<String>();
            voice_text.trim();            // 去除首尾空白字符
            voice_text.replace("[", "");  // 去除左方括号
            voice_text.replace("]", "");  // 去除右方括号
            voice_text.replace("\"", ""); // 去除双引号

            // Serial.println(voice_text);

            if (mic_move_flag)
            {
                if (voice_text.indexOf("前进") != -1)
                {
                    move_flag = true;
                    action = 0;
                }
                else if (voice_text.indexOf("旋转") != -1)
                {
                    move_flag = true;
                    action = 4;
                }
                else if (voice_text.indexOf("波浪") != -1)
                {
                    move_flag = true;
                    action = 5;
                }
                else if (voice_text.indexOf("俯卧撑") != -1)
                {
                    move_flag = true;
                    action = 6;
                }
            }
            else
            {
                voice_answer = get_GPTanswer(voice_text);
                baiduTTS_Send(voice_answer);
                // Serial.println(voice_answer);
            }
        }
    }
    else
    {
        Serial.printf("[HTTP] POST failed, error: %s\n", http_text.errorToString(httpCode).c_str());
    }
    http_text.end();
}

// 没用
void getToSTT(void)
{
    voice_answer = "你好，我是你的机器人助手。";

    data_json2 = "{\"voice_id\": \"male-qn-qingse\",\"text\":\"" + voice_answer + "\",\"model\": \"speech-01\",\"speed\": 1.0,\"vol\": 1.0,\"pitch\": 0,\"audio_sample_rate\": 24000,\"bitrate\": 128000}";

    HTTPClient http_voice;
    // http_voice.begin("https://tsn.baidu.com/text2audio?tex="+encode+"&lan=zh&cuid="+ID+"&ctp=1&tok="+token);
    http_voice.begin("https://api.minimax.chat/v1/t2a_pro?GroupId={" + GroupID + "}");
    http_voice.addHeader("Authorization", GroupKey);
    http_voice.addHeader("Content-Type", "application/json");

    int httpCode = http_voice.POST(data_json2);

    if (httpCode > 0)
    {
        if (httpCode == HTTP_CODE_OK)
        {
            String payload = http_voice.getString();
            DynamicJsonDocument doc(4096);
            DeserializationError error = deserializeJson(doc, payload);
            Serial.println(payload);

            if (error)
            {
                Serial.print("deserializeJson() failed: ");
                Serial.println(error.c_str());
            }

            voice_get = doc["audio_file"].as<String>();
            Serial.println(voice_get);
            audio.connecttohost(voice_get.c_str());
        }
    }
    else
    {
        Serial.printf("[HTTP] POST failed, error: %s\n", http_voice.errorToString(httpCode).c_str());
    }
    http_voice.end();
}

// 没有用上
String gainToken(void) // 获取token
{
    HTTPClient http_token;
    String token;

    String url = String("https://aip.baidubce.com/oauth/2.0/token?grant_type=client_credentials&client_id=") + API_KEY + "&client_secret=" + SECRET_KEY;

    http_token.begin(url);
    int httpCode = http_token.GET();

    if (httpCode > 0)
    {
        if (httpCode == HTTP_CODE_OK)
        {
            String payload = http_token.getString();
            DynamicJsonDocument doc(1024);
            deserializeJson(doc, payload);
            token = doc["access_token"].as<String>();
        }
    }
    else
    {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http_token.errorToString(httpCode).c_str());
    }
    http_token.end();

    return token;
}

void aseembleJson(String token)
{
    memset(data_json, '\0', strlen(data_json)); // 将数组清空
    strcat(data_json, "{");
    strcat(data_json, "\"format\":\"pcm\",");
    strcat(data_json, "\"rate\":16000,");        // 采样率    如果采样率改变了，记得修改该值，只有16000、8000两个固定采样率
    strcat(data_json, "\"dev_pid\":1537,");      // 中文普通话
    strcat(data_json, "\"channel\":1,");         // 单声道
    strcat(data_json, "\"cuid\":\"04190906\","); // 识别码    随便打几个字符，但最好唯一
    strcat(data_json, "\"token\":\"");
    strcat(data_json, token.c_str()); // 这里需要修改成自己申请到的token
    strcat(data_json, "\",");
    sprintf(data_json + strlen(data_json), "\"len\":%d,", adc_data_len * 2); // 数据长度 如果传输的数据长度改变了,记得修改该值,该值是ADC采集的数据字节数,不是base64编码后的长度
    strcat(data_json, "\"speech\":\"");
    strcat(data_json, base64::encode((uint8_t *)adc_data, adc_data_len * sizeof(uint16_t)).c_str()); // base64编码数据
    strcat(data_json, "\"");
    strcat(data_json, "}");
}

void removeBrackets(String str)
{
    int len = strlen(str.c_str()) + 2;
    int i, j = 0;

    // 遍历字符串，将非方括号的字符复制到原字符串中
    for (i = 0; i <= len; i++)
    {
        if (str[i] != '"' && str[i] != '[' && str[i] != ']')
        {
            str[j] = str[i];
            j++;
        }
    }

    // 添加字符串结束符
    str[j] = '\0';
}

portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;
void IRAM_ATTR onTimer()
{
    portENTER_CRITICAL_ISR(&timerMux);

    if (adc_start_flag == 1)
    {
        // if(!adc_read_flag)adc_read_flag = 1;
        adc_data[num] = analogRead(ADC_OUT);
        num++;
        if (num >= adc_data_len)
        {
            adc_complete_flag = 1;
            adc_start_flag = 0;
            num = 0;
        }
    }

    portEXIT_CRITICAL_ISR(&timerMux);
}

void baiduTTS_Send(String text)
{
    if (text.length() == 0)
    {
        Serial.println("text is null");
        return;
    }

    const int per = 1;
    const int spd = 2;
    const int pit = 5;
    const int vol = 10;
    const int aue = 6;

    // 进行 URL 编码
    String encodedText = urlEncode(urlEncode(text));

    // URL http请求数据封装
    String url = "https://tsn.baidu.com/text2audio";

    const char *header[] = {"Content-Type", "Content-Length"};

    url += "?tok=" + token;
    url += "&tex=" + encodedText;
    url += "&per=" + String(per);
    url += "&spd=" + String(spd);
    url += "&pit=" + String(pit);
    url += "&vol=" + String(vol);
    url += "&aue=" + String(aue);
    url += "&cuid=esp32s3";
    url += "&lan=zh";
    url += "&ctp=1";

    // http请求创建
    HTTPClient http;

    http.begin(url);
    http.collectHeaders(header, 2);

    // http请求
    int httpResponseCode = http.GET();
    if (httpResponseCode > 0)
    {
        if (httpResponseCode == HTTP_CODE_OK)
        {
            String contentType = http.header("Content-Type");
            Serial.println(contentType);
            if (contentType.startsWith("audio"))
            {
                Serial.println("合成成功");

                // 获取返回的音频数据流
                Stream *stream = http.getStreamPtr();
                uint8_t buffer[512];
                size_t bytesRead = 0;

                // 设置timeout为200ms 避免最后出现杂音
                stream->setTimeout(200);
                clearAudio();
                while (http.connected() && (bytesRead = stream->readBytes(buffer, sizeof(buffer))) > 0)
                {
                    // 音频输出
                    playAudio(buffer, bytesRead);
                    delay(1);
                }

                // 清空I2S DMA缓冲区
                clearAudio();
            }
            else if (contentType.equals("application/json"))
            {
                Serial.println("合成出现错误");
            }
            else
            {
                Serial.println("未知的Content-Type");
            }
        }
        else
        {
            Serial.println("Failed to receive audio file");
        }
    }
    else
    {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
    }
    http.end();
}

// Play audio data using MAX98357A
void playAudio(uint8_t *audioData, size_t audioDataSize)
{
    if (audioDataSize > 0)
    {
        // 发送
        size_t bytes_written = 0;
        i2s_write(I2S_NUM_0, (int16_t *)audioData, audioDataSize, &bytes_written, portMAX_DELAY);
        // esp_err_t err = i2s_write((i2s_port_t) m_i2s_num, (const char*) &s32, sizeof(uint32_t), &m_i2s_bytesWritten, 1000);
    }
}

void clearAudio(void)
{
    // 清空I2S DMA缓冲区
    i2s_zero_dma_buffer(I2S_NUM_0);
    Serial.print("clearAudio");
}
