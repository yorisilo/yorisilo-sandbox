#!/usr/bin/env ruby
require 'webrick'
require 'pry'


# http://morimoru.blogspot.jp/2008/12/webrickhttpservletabstractservlet.html

# サーブレット
class TestContentServlet < WEBrick::HTTPServlet::AbstractServlet
  def do_GET(req, res)
    res.content_type = WEBrick::HTTPUtils.mime_type(
      req.path_info,
      WEBrick::HTTPUtils::DefaultMimeTypes)
    res.body = "This is #{req.path}<br>"
    binding.pry
  end
end

# http サーバー
srv = WEBrick::HTTPServer.new(BindAddress: '127.0.0.1', Port: 7777)

# サーブレットをマウント
srv.mount('/', TestContentServlet)

# Ctrl + C で停止させるためのトラップを仕込む
trap("INT"){ srv.shutdown }

# サーバーの起動
srv.start
