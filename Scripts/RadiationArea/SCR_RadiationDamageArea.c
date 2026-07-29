class SCR_RadiationDamageArea : SCR_DamageArea
{
	[Atribute()]
	float m_fEmissionRate;
	
	//------------------------------------------------------------------------------------------------
	//! Callback when an entity enters this DamageArea this frame
	//! \param[in] entity
	override void OnAreaEntered(notnull IEntity entity)
	{
		SCR_ExtendedDamageManagerComponent damageManagerExt = SCR_ExtendedDamageManagerComponent.Cast(SCR_DamageManagerComponent.GetDamageManager(entity));
		if (!damageManagerExt)
			return;
		
		array<HitZone> allHitZones = {};
		damageManagerExt.GetAllHitZones(allHitZones);
		 if (allHitZones.IsEmpty())
			return;
		
		//bool effectApplied = IsEffectApplied(entity);
		array<ref SCR_PersistentDamageEffect> damageEffects = {};
		if (damageManager.FindAllDamageEffectsOfType(GetDamageEffect().Type(), damageEffects) < 1)
			return false;
		
		map<HitZone, SCR_PersistentDamageEffect> allHitzonesAffected = new map<HitZone, SCR_PersistentDamageEffect>();
		foreach (SCR_PersistentDamageEffect dmgEffect : damageEffects)
		{
			allHitzonesAffected.Insert(dmgEffect.GetAffectedHitZone(), dmgEffect);
		}
		
		foreach (HitZone hitZone : allHitZones)
		{
			SCR_RadiationDamageEffect radiationDamage;
			if (!allHitzonesAffected.Contains(hitZone))
			{
				radiationDamage = new SCR_RadiationDamageEffect;
				
				// Set hitzone and add the effect
				Print("Adding effect");
			}
			else
			{
				radiationDamage = allHitzonesAffected.Get(hitZone);
			}
				
			radiationDamage.AddRadiationAreas(GetOwner());
		}
	}
	
	//------------------------------------------------------------------------------------------------
	//! Callback when an entity exits this DamageArea this frame
	//! \param[in] entity
	override void OnAreaExit(IEntity entity)
	{
		// Remove here refs to the owner
		super.OnAreaExit(entity);
		
		
	}
	
	//------------------------------------------------------------------------------------------------
	float GetRadiationEmissionRate()
	{
		return m_fEmissionRate;
	}
}