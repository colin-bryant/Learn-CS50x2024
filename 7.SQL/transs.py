import speech_recognition as sr
import requests
import json

# 语音识别
def recognize_speech(audio_file):
    recognizer = sr.Recognizer()
    with sr.AudioFile(audio_file) as source:
        audio_data = recognizer.record(source)
    return recognizer.recognize_google(audio_data, language='en-US')

# 文本翻译
def translate_text(text):
    url = "https://api.deeplx.org/translate"
    payload = json.dumps({
      "text": text,
      "source_lang": "auto",
      "target_lang": "zh"
    })
    headers = {
      'Content-Type': 'application/json'
    }
    response = requests.request("POST", url, headers=headers, data=payload)
    json_response = json.loads(response.text)
    translated_text = json_response['data']
    return translated_text

# 保存翻译结果到文件
def save_to_file(text, output_file_path):
    with open(output_file_path, "w", encoding="utf-8") as output_file:
        output_file.write(text)

# 主函数
def main():
    audio_file_path = "audio_file.wav"
    translated_output_path = "translated_text.txt"

    # 语音识别
    recognized_text = recognize_speech(audio_file_path)

    # 文本翻译
    translated_text = translate_text(recognized_text)

    # 保存翻译结果到文件
    save_to_file(translated_text, translated_output_path)

    print("翻译结果已保存到文件:", translated_output_path)

if __name__ == "__main__":
    main()
