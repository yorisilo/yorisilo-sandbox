require "spec_helper"

# [1,4,4,5,6,4,5,5,10,0,1,7,3,6,4,10,2,8,6] => 133

# [10,10,10,10,10,10,10,10,10,10,10,10,10] => 300

# 10 frame
# 1 roll / 1..9 frame but last 2or3 roll / 10 frame

# ストライク
# １投目で10本全部倒した場合。ストライクを足したフレームの得点は、次の２投分を加算する
# [10＋○＋○]。ストライクが続くと高得点になる。２回続いたら３フレーム目の１投目までを
# 加算[10＋10＋○]。

# スペア
# １投目で残ったピンを、２投目で全部倒すと「スペア」。次の１投分を加算することができる
# [10＋○]。スペアをとるか、とらないかでは、約10点の差が出る。

describe Game, 'すべてガターの場合' do
  let(:score_sheet) { [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0] }
  let(:game) { Game.new(score_sheet) }

  it 'スコアは0点' do
    expect(game.score).to eq 0
  end
end

describe Game, 'すべて1ピンの場合' do
  let(:score_sheet) { [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1] }
  let(:game) { Game.new(score_sheet) }

  it 'スコアは20点' do
    expect(game.score).to eq 20
  end
end

describe Game, 'ストライクを一回とった場合' do
  let(:score_sheet) { [10,3,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0] }
  let(:game) { Game.new(score_sheet) }

  it 'スコアは24点' do
    expect(game.score).to eq 24
  end
end

describe Game, 'スペアを1回とった場合' do
  let(:score_sheet) { [7,3,2,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0] }
  let(:game) { Game.new(score_sheet) }

  it 'スコアは20点' do
    expect(game.score).to eq 20
  end
end

describe Game, 'パーフェクトゲームの場合' do
  let(:score_sheet) { [10,10,10,10,10,10,10,10,10,10,10,10,10] }
  let(:game) { Game.new(score_sheet) }

  it 'スコアは300点' do
    expect(game.score).to eq 300
  end
end

# [1,4,4,5,6,4,5,5,10,0,1,7,3,6,4,10,2,8,6] => 133
describe Game, 'Uncle Bob の受け入れスコア' do
  let(:score_sheet) { [1,4,4,5,6,4,5,5,10,0,1,7,3,6,4,10,2,8,6] }
  let(:game) { Game.new(score_sheet) }

  it 'スコアは133点' do
    expect(game.score).to eq 133
  end
end

# describe Game, 'スペアを途中で1回とった場合' do
#   let(:game) { Game.new }
#   let(:score_sheet) { [6,2,10,2,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0] }

#   before do
#     inputScoreSheet(game, score_sheet)
#   end

#   it 'スコアは点' do
#     expect(game.score).to eq
#   end
# end

private

def inputScoreSheet(score_sheet)
  score_sheet.each do |e|
    game.roll(e)
  end
end

def roll_strike
  game.roll(10)
end

def roll_gutter
  game.roll(0)
end
