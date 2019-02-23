require "securerandom"

describe 'database' do
  def run_script(commands, database_name = SecureRandom.hex)
    raw_output = nil

    IO.popen("./db data/" + database_name, "r+") do |pipe|
      commands.each do |command|
        pipe.puts command
      end

      pipe.close_write

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
      ">",
      ".",
      ">(1, user1, person1@example.com)",
      ">."
    ])
  end

  it 'prints error message when table is full' do
    script = (1..1401).map do |i|
      "insert #{i} user#{i} person#{i}@example.com"
    end
    script << ".die"
    result = run_script(script)
    expect(result[-2]).to eq('>No more space left in table.')
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
      ">",
      ".",
      ">(1, #{long_username}, #{long_email})",
      ">.",
    ])
  end

  it 'prints error message if strings are too long' do
    long_username = "a"*33
    long_email = "a"*256
    script = [
      "insert 1 #{long_username} #{long_email}",
      "select",
      ".die",
    ]
    result = run_script(script)
    expect(result).to match_array([
      ">",
      ">String is too long!",
      ">.",
    ])
  end

  it 'prints an error message if id is negative' do
    script = [
      "insert -1 cstack foo@bar.com",
      "select",
      ".die",
    ]
    result = run_script(script)
    expect(result).to match_array([
      ">",
      ">ID must be positive.",
      ">.",
    ])
  end


 # Test for persistance.
  it 'keeps data after closing connection' do
    random_database_name = SecureRandom.hex
    result1 = run_script([
      "insert 1 u1 person1@example.com",
      ".die",
    ], random_database_name)
    expect(result1).to match_array([
      ">",
      ">."
    ])
    result2 = run_script([
      "select",
      ".die",
    ], random_database_name)
    expect(result2).to match_array([
      ">(1, u1, person1@example.com)",
      ".",
      ">",
    ])
  end
end
