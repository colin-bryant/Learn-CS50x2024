import requests
import json

url = "https://api.deeplx.org/translate"
# text ="Hello, world!     hello, fangfang"
# 读取文本文件内容
with open("linux.srt", "r", encoding="utf-8") as file:
    text = file.read()

payload = json.dumps({
  "text": text,
  "source_lang": "auto",
  "target_lang": "ZH"
})
headers = {
  'Content-Type': 'application/json'
}

response = requests.request("POST", url, headers=headers, data=payload)

# 解析 JSON 响应
json_response = json.loads(response.text)

# 提取翻译后的文本内容
translated_text = json_response['data']



# 定义新文件名
output_file_name = "linuz_zh.srt"

# 写入翻译后的文本到新文件中
with open(output_file_name, "w", encoding="utf-8") as output_file:
    output_file.write(translated_text)

print(f"翻译后的文本已经写入到 {output_file_name} 文件中。")
