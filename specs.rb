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
end
