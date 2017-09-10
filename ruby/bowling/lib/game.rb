class Game
  FRAME_OF_A_GAME = 10

  def initialize(rolls=[])
    @rolls = rolls
  end

  def roll(pins)
    @rolls << pins
  end

  def score
    # @rolls.reduce(:+)
    # @rolls.inject(0) { |injection, element| injection + element }
    roll_idx = 0
    score = 0
    FRAME_OF_A_GAME.times do
      if strike?(roll_idx)
        score += 10 + strike_bonus(roll_idx)
        roll_idx += 1
      elsif spare?(roll_idx)
        score += 10 + spare_bonus(roll_idx)
        roll_idx += 2
      else
        score += @rolls[roll_idx] + @rolls[roll_idx + 1]
        roll_idx += 2
      end
    end
    score
  end

  def scoreOnEveryFrame
    roll_idx = 0
    frames = []

    FRAME_OF_A_GAME.times do |frame|
      if strike?(roll_idx)
        if frame == 9
          frames << [@rolls[roll_idx], @rolls[roll_idx + 1], @rolls[roll_idx + 2]]
        else
          frames << [@rolls[roll_idx]]
          roll_idx += 1
        end
      elsif spare?(roll_idx)
        if frame == 9
          frames << [@rolls[roll_idx], @rolls[roll_idx + 1], @rolls[roll_idx + 2]]
        else
          frames << [@rolls[roll_idx], @rolls[roll_idx + 1]]
          roll_idx += 2
        end
      else
        frames << [@rolls[roll_idx], @rolls[roll_idx + 1]]
        roll_idx += 2
      end
    end
    frames
  end

  def scoreAt(frame_num)
    frame_num = frame_num - 1
    scoreOnEveryFrame[frame_num]
  end

  private

  def strike?(roll_idx)
    @rolls[roll_idx] == 10
  end

  def spare?(roll_idx)
    @rolls[roll_idx] + @rolls[roll_idx + 1] == 10
  end

  def strike_bonus(roll_idx)
    @rolls[roll_idx + 1] + @rolls[roll_idx + 2]
  end

  def spare_bonus(roll_idx)
    @rolls[roll_idx + 2]
  end
end
