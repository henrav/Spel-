
print("Lua patch loaded")

function Entity:damage(amount)
    self:setHealth(self:getHealth() - amount)
end
