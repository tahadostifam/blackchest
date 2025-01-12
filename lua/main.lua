-- Define a variable
local x = 10

-- Nested if-else blocks
if x > 0 then
  print("x is positive")
  if x < 10 then
    print("x is less than 10")
  elseif x == 10 then
    print("x is equal to 10")
  else
    print("x is greater than 10")
  end
elseif x < 0 then
  print("x is negative")
else
  print("x is zero")
end