# 概要
このソフトウェアは、Web Bluetooth APIを利用し、ブラウザ（Chrome）から、micro:bitに接続されたNeopixel系のLEDをコントロールするためのサンプルプログラムです。

![Image](https://raw.githubusercontent.com/carcon999/kirakira_webble/master/img/general.png)

ソフトウェアは、2種類にわかれます。
* micro:bitに配置するArduino IDEで開発されたソフト
  https://github.com/carcon999/kirakira_webble/tree/master/kirakira_webble

* Chromeで呼び出されることになる、Web Bluetooth APIを利用したJavascript
  https://github.com/carcon999/kirakira_webble/tree/master/html

# ビルド方法(micro:bit)
まず、micro:bitに配置するプログラムをビルドする必要があります。
こちらで説明しているビルド方法の 1. ～　3. の手順でArduino IDEを準備してください。
https://github.com/carcon999/kirabitDemo/blob/master/README.md

ビルドを実施したら、micro:bitにUSBケーブルを接続し、書き込みを実施します。

# ビルド方法(Javascript)
1. ファイルを一式、Webサーバへ配置します。
1. Webサーバは、Httpsでアクセスできる環境が必要となります。
1. ご利用できるブラウザは、Chromeのみです。最新版のChromeで実行してください。

# 実行方法

1. micro:bitとLEDに電源を供給します。
1. micro:bitの5x5LEDに□が表示されていることを確認します。
1. ChromeでWebサーバに配置したURLを表示します。
1. ブラウザ上の'connect'ボタンを押下します。
1. ペアリング設定画面が表示されるので、その一覧から、'kirakirabit'を選択します。
1. 正常に接続できると、ボタンの右側に'connect'の表示がされます。
1. あとは、スライダーを操作することで自由に色を変更できます。
1. ブラウザ上の'Disconnect'ボタンを押下すると、Bluetoothの接続が解除されます。LEDも消灯します。

#公開URL
下記のURLから試すことができます。
Chromeを利用してください。
https://s3-ap-northeast-1.amazonaws.com/microbitble/webble.html

# オプション

サンプルプログラムは、[kirakira:bit](https://www.switch-science.com/catalog/3923/)のLED40個ですが、Kitronikの[ZIP Halo for the BBC micro:bit](https://www.switch-science.com/catalog/3484/)でも動作します。

![Image](https://raw.githubusercontent.com/carcon999/kirakira_webble/master/img/20180911_000408.jpg)

その場合は、Arduino側のプログラムのLEDポート番号を１番から０番を利用するように変更してください。

```c
//#define LED_PIN         1     // LED出力PIN番号
#define LED_PIN         0     // LED出力PIN番号 こちら
```

# ブログ紹介

こちらのブログでも、本件の内容を説明していますので、合わせてご覧ください。

[Web Bluetooth APIを使ってNeopixelを制御する](https://blogs.yahoo.co.jp/carcon999/40242528.html)
