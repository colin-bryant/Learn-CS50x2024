import qrcode

# 中文文本
# text = ""

# 将中文文本转换为字节字符串
# text_bytes = text.encode('utf-8')
# 生成二维码
img=qrcode.make("https://youtu.be/xvFZjo5PgG0")
# 保存二维码图片
img.save("qr.png","PNG")

