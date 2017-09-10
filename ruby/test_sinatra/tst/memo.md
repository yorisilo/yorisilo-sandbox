# sinatra アプリ
[ruby を 扱うときに出てくる用語たちの説明](http://www.ownway.info/Ruby/glossary )
[sinatra readme ja](http://www.sinatrarb.com/intro-ja.html )
[webアプリの仕組み](http://www.slideshare.net/satococoa/sinatraweb-9030444?related=3 )

### Ref
http://www.machu.jp/diary/20111002.html#p01
http://woshidan.hatenablog.com/entry/2014/07/20/160006
https://it.typeac.jp/article/show/7
http://qiita.com/7kaji/items/6a59977d2ad85604e7fd

## 流れ

```sh
$ touch Gemfile # 適当にGemfileを書く
source "https://rubygems.org"
ruby "2.2.2"
gem 'sinatra'
gem 'sinatra-contrib'
gem 'foreman'

group :development, :test do
  gem 'what_methods'
  gem 'wirb'
  gem 'save-history'
end

$ bundle install --path vendor/bundle # 2回目からは bundle install のみでおｋ

$ touch Procfile # Herokuの起動ファイル foremanからProcfileを読み込む
web: bundle exec ruby web.rb -p $PORT
web: bundle exec rackup config.ru -p $PORT # config.ruを使うならこうらしい

$ bundle exec foreman start # webサーバが起動する
```

### foreman
* foreman は、Procfile を読み込み、複数のプロセスを管理できるツール．
Heroku を動かす際にも用いられている．
* foremanは依存するバックグラウンドプロセスを簡単に管理できる．

* 準備
アプリケーションで管理するプロセスを Procfile に記述し、アプリケーションルートに配置。
* Procfile の書き方
  * <process type>: <command>
  process type : web, worker, clock などが代表的で、名前はなんでもよい。
  (Heroku では web は特別で、この名前が Heroku ルータからの HTTP を受け付ける。)
  * Procfile

  ```ruby
  web: bundle exec rails server -p $PORT  # rails 起動($PORTは5000がデフォ)
  worker: bundle exec rake jobs:worK      # バッチ起動
  redis: bundle exec redis-server /usr/local/etc/redis.conf  # Redis 起動
  ```
* 起動
  `$ bundle exec foreman start`
  これで、Procfile に設定したすべてのプロセスを一度に起動することができる。
  終了は Ctrl + c

* ローカルの開発環境で開発やデバックを行う際、リモートの環境と同じ状態で実行することは重要です。 このことは、互換性が無いことや、発見が難しいバグを本番環境へディプイする前に見つけ出すことを保証してくれます。 また、個々のコマンドが独立して機能する一連の流れに代わり、１つの集合体としてアプリケーションを扱います。
Foremanは、`Procfile` の後方で動作する アプリを動かすためのコマンドラインツールです。Heroku Toolbeltにより自動的にインストールされ、 Ruby Gemとしても利用可能です。

http://qiita.com/7kaji/items/6a59977d2ad85604e7fd


### webserver
http://edywrite.blogspot.jp/2012/08/herokuwebthin.html

#### webrick
Heroku上のデフォルトのwebサーバーはwebrickである．
Herokuでも実運用ではthinを使うように推奨している．
thinはコンパクトでWEBrickよりも速く技術的にも枯れていて，普通のWEBサイトであれば十分な性能をもっている．

### config.ru
* サーバでアプリケーションを立ち上げるとき，
環境設定を行うためのプログラム郡を呼び出すのに使われる．
* Procfileに書かれた内容に従ってwebサーバを立ち上げたときの環境設定を行うファイルの読み込み処理などを書く．

### Procfile
https://github.com/herokaijp/devcenter/wiki/procfile
* Procfileはherokuのアプリケーションの中で行われるプロセスの立ち上げ等を書くファイル．
* Herokuの起動ファイル
* foremanからProcfileを読み込む

#### example
* Procfile

```ruby
web: bundle exec rackup config.ru -p $PORT
```
ここにwebプロセスの立ち上げを

web: bundle exec rackup config.ru -p $PORT

というふうに書いておかないとエラーになる．

ここに書かれたプロセスによってweb Dyno(Webプロセス用のサーバ)やcron Dyno(Cronプロセス用のサーバ)が確保されます。

phpのファイルをProcfileなしの単体でつっこんだときは、webプロセスを１つ立ち上げるようになっているみたい．


* config.ru

```ruby
require 'bundler'
Bundler.require

require './config.rb' # sinatraでルーティングを書いているrbファイル
run Sinatra::Application
```
* config.rb
ルーティングなど環境変数の設定が書かれたrbファイル
今回は，こんな感じ．

```ruby
require 'rubygems'
require 'sinatra'

get '/' do
erb :index # views/index.erbの読み込み
end
```

#### example
http://hyottokoaloha.hatenablog.com/entry/2015/05/03/164947
sinatraで動かしてるサービスをherokuにあげるときに少し手間が必要なので書きます。
作業ディレクトリにconfig.ruを作成

* config.ru

```ruby
require "./myapp"
run Sinatra::Application
```

次に同じ場所にProcfileを作成

* Procfile

```ruby
web: bundle exec rackup config.ru -p $PORT
```

* Gemfile に以下を追加

```ruby
gem 'rack'
```
以上．
