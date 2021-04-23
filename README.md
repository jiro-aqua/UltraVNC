# UltraVNC

UltraVNC Server and UltraVNC Viewer

Required compilers

Visual Studio 2017 or 2019

nasm assembler compiler (https://www.nasm.us/)

Load the project files vncviewer_vs2017.sln and winvncVS2017.sln to build server or viewer.

# カスタム版 Ultra VNC Viewer

以下、文責 @jiro-aqua

自分用にカスタマイズしたものを置いておきます。
Windows 10/US Keyboard 環境から Mac に繋ぐためのものです。

内容は以下の通り。

- ALT+`をリモートに通すようにした。

  Windows10 は ALT+\`を VK_KANJI という仮想キーに変換してしまうため、VNC クライアントはこのキーコンビネーションを適切に扱えません。  
  この対応として、VK_KANJI を検出したら、GRAVE(\`)キーの DOWN/UP を送るように改造しました。 Mac 側の IME 切替キーを cmd+\`に変更しておくと、Mac と VNC 経由の Windows で同じ配列で IME 切替が出来るようになります。

- Win キーを Option キーとして使えるようにした  
  　 Ultra VNC Viewer は Win キーを XK_Super_L/R キーとして VNC サーバに送出します。  
  　 Mac では、これを cmd キーとして解釈するため、option キーとして使えません。  
  　ので、Win キーに対して、XK_Meta_L/R キーを送出するように改造しました。

- 特殊キーを常にサーバに送るようにした  
  　 Ultra VNC Viewer は ScrollLock がかかっている間、特殊キーをサーバに送る仕様になっていますが、これを常に有効になるように改造しました。

Macbook を持ち出さない時にヘッドレス RDP での運用が出来るように、個人的好みで改造してあります。

お好みに応じて差分を取り込んでください。

バイナリの配布はしません。

# ビルド方法補足

Visual Studio 2017 Community Edition を使用します。
Ultra VNC が Windows 8.1 SDK に依存しているためです。(2019 だと 8.1 SDK がダウンロード出来ないので)

vncviewer/vncviewer_vs2017.sln を開き、ビルドしてください。

途中、libjpeg-turbo-win でビルドが失敗します。  
nasm というアセンブラを外部起動しているためです。  
https://www.nasm.us/  
上記リンクから Download して、インストールしてください。  
C:\Users\[ユーザー名]\AppData\Local\bin\NASM  
にインストールされるので、libjpeg-turbo-win ＞プロパティ＞ VC++ディレクトリ＞実行可能ファイル ディレクトリ、のパスを書き替えましょう。

多分ここまでやればビルド出来るはず。
