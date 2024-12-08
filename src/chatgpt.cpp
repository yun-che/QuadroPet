#include <chatgpt.h>

// String url_3 = "https://aip.baidubce.com/rpc/2.0/ai_custom/v1/wenxinworkshop/chat/completions?access_token=24.d48bb2dbb7cc5c50af9030da72387457.2592000.1712976820.282335-56444788";
String url_4 = "https://api.minimax.chat/v1/text/chatcompletion_v2";
String MiniMaxKey = (String) "Bearer " + "eyJhbGciOiJSUzI1NiIsInR5cCI6IkpXVCJ9.eyJHcm91cE5hbWUiOiLovrDlsbEiLCJVc2VyTmFtZSI6Iui-sOWxsSIsIkFjY291bnQiOiIiLCJTdWJqZWN0SUQiOiIxODEwNTQxMzM2MTEwMDU2MzMyIiwiUGhvbmUiOiIxODkyNzA4MzMzOSIsIkdyb3VwSUQiOiIxODEwNTQxMzM2MTAxNjY3NzI0IiwiUGFnZU5hbWUiOiIiLCJNYWlsIjoiIiwiQ3JlYXRlVGltZSI6IjIwMjQtMDgtMjUgMTc6MjI6MzUiLCJpc3MiOiJtaW5pbWF4In0.d74ko6g0fu4hRkIlaj6qPK0ZgkZH-38c2WF3_tlz2L1PHoGB8RBFcjBDiB5X93XxBOdv2cUNFMM3AV20R-npXmPFZp7-OBtPixZvplL4jO3J1h3cRhKpOb8GRPUZQzj6gYosbuzQtjAvoAgcbHZrWiMPHP9sK5qfLVxX2GGecV3-QutU8jXW-MZ8BU91jvfthTcvdzBzeYcYNIXSE66Kkq6zjY1hAU0qy86k8C7fe7BEDRGwUiMO6sBVxLF4Sps3TAtoEX4q8oeAJCr7U1zRzD1NPBFRIBRHZ1q931Ngngp-O6CvDrf8DiVt3Waeiq4BiLAE6BPQFPkE2A2HtH4ZFQ";

String get_GPTanswer(String question)
{
    HTTPClient http_3;
    http_3.setTimeout(20000);
    http_3.begin(url_4);
    http_3.addHeader("Content-Type", "application/json");
    http_3.addHeader("Authorization", MiniMaxKey);

    String data = //"{\"messages\":[{\"role\": \"user\",\"content\": \"" + question + "\"}],\"disable_search\": false,\"enable_citation\": false}";
        "{\"model\":\"abab5.5s-chat\",\"messages\":[{\"role\": \"system\",\"content\": \"你是一个聊天机器人，要求下面的回答严格控制在60字以内。\"},{\"role\": \"user\",\"content\": \"" + question + "\"}]}";
    int httpResponseCode = http_3.POST(data);

    if (httpResponseCode == 200)
    {
        String response = http_3.getString();
        DynamicJsonDocument doc(4096);
        DeserializationError error = deserializeJson(doc, response);

        if (error)
        {
            Serial.print("deserializeJson() failed: ");
            Serial.println(error.c_str());
            return "<error>";
        }

        String answer = // doc["result"].as<String>();
            doc["choices"][0]["message"]["content"].as<String>();
        http_3.end();
        return answer;
    }
    else
    {
        Serial.print("HTTP POST request failed, error code: ");
        Serial.println(httpResponseCode);
        http_3.end();
        return "<error>";
    }
}

// 没用上
void GPTtest(void)
{
    if (Serial.available())
    {
        String question = Serial.readStringUntil('\n');
        question.trim();
        Serial.println("Question: " + question);

        String answer = get_GPTanswer(question);
        Serial.println("Answer: " + answer);

        Serial.println("Enter question:");
    }
}