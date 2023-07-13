# q-learning
- [CartPoleでQ学習（Q-learning）を実装・解説【Phythonで強化学習：第1回】](http://neuro-educator.com/rl1/)

# python の開発環境
- [pyenv、pyenv-virtualenv、venv、Anaconda、Pipenv。私はPipenvを使う。 - Qiita](https://qiita.com/KRiver1/items/c1788e616b77a9bad4dd)
新しくプロジェクトを立ち上げる際やること

``` python
$ mkdir project1  # Projectを作成
$ cd project1  # Projectに移動
$ pipenv install  # 仮想環境を作成
$ pipenv shell  # サブシェルを立ち上げて仮想環境に入る
$ exit # サブシェルを閉じることで仮想環境からも出る

$ pipenv install gym # pip install の代わりに使う。bundle install 的な感じ
$ pipenv run pip freeze # 仮想環境にインストールされているライブラリの確認
```

`pip install <-> gem install`
`pipenv install <-> bundle install`

- [Pythonで、Pipenvを使う - Narito Blog](https://narito.ninja/blog/detail/58/)
