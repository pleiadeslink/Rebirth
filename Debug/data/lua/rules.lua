function calculatePhysicalDamage()
	return 2
end

function calculateMaxHealth(actor)
	health = getConstitution(actor)
	return health * 5 + 2
end