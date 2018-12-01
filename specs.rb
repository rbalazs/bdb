# docker-compose run tester rspec specs.rb
# ; )

describe 'database' do
  def run_script(commands)
    raw_output = nil
    IO.popen("./db", "r+") do |pipe|
      commands.each do |command|
        pipe.puts command
      end

      pipe.close_write

      # Read entire output
      raw_output = pipe.gets(nil)
    end
    raw_output.split("\n")
  end

  it 'inserts and retreives a row' do
    result = run_script([
      "insert 1 user1 person1@example.com",
      "select",
      ".die",
    ])
    expect(result).to match_array([
      "bdb > .",
      "bdb > (1, user1, person1@example.com)",
      ".",
      "bdb > ",
    ])
  end

  it 'prints error message when table is full' do
    script = (1..1401).map do |i|
      "insert #{i} user#{i} person#{i}@example.com"
    end
    script << ".die"
    result = run_script(script)
    expect(result[-2]).to eq('bdb > No more space left in table.')
  end

  it 'allows inserting strings that are the maximum length' do
    long_username = "u"*32
    long_email = "e"*255
    script = [
      "insert 1 #{long_username} #{long_email}",
      "select",
      ".die",
    ]
    result = run_script(script)
    expect(result).to match_array([
      "bdb > .",
      "bdb > (1, #{long_username}, #{long_email})",
      ".",
      "bdb > ",
    ])
  end
end
