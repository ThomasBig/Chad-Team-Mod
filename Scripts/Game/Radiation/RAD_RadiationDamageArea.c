class RAD_RadiationDamageArea : SCR_DamageArea
{
	[Attribute()]
	float m_fEmissionRate;
	
	//------------------------------------------------------------------------------------------------
	//! \return
	override bool IsRegisteredAutomatically()
	{
		return true;
	}
	
	protected void PlaySound()
	{	
		SoundComponent soundComp = SoundComponent.Cast(GetParent().FindComponent(SoundComponent));
		 
		if (!soundComp)
		    return;
		 
		soundComp.SoundEvent("Radiation");
	}
	
	//------------------------------------------------------------------------------------------------
	//! Callback when an entity enters this DamageArea this frame
	//! \param[in] entity
	override void OnAreaEntered(notnull IEntity entity)
	{
		Print("it enters");
		PlaySound();
		SCR_ExtendedDamageManagerComponent damageManagerExt = SCR_ExtendedDamageManagerComponent.Cast(SCR_DamageManagerComponent.GetDamageManager(entity));
		if (!damageManagerExt)
			return;
		
		array<HitZone> allHitZones = {};
		damageManagerExt.GetAllHitZones(allHitZones);
		 if (allHitZones.IsEmpty())
			return;
		
		array<ref SCR_PersistentDamageEffect> damageEffects = {};
		damageManagerExt.FindAllDamageEffectsOfType(GetDamageEffect().Type(), damageEffects);
		
		map<HitZone, SCR_PersistentDamageEffect> allHitzonesAffected = new map<HitZone, SCR_PersistentDamageEffect>();
		foreach (SCR_PersistentDamageEffect dmgEffect : damageEffects)
		{
			allHitzonesAffected.Insert(dmgEffect.GetAffectedHitZone(), dmgEffect);
		}
		
		foreach (HitZone hitZone : allHitZones)
		{
			RAD_RadiationDamageEffect radiationDamage;
			if (!allHitzonesAffected.Contains(hitZone))
			{
				radiationDamage = new RAD_RadiationDamageEffect;
				radiationDamage.SetAffectedHitZone(hitZone);
				damageManagerExt.AddDamageEffect(radiationDamage);
			}
			else
			{
				radiationDamage = RAD_RadiationDamageEffect.Cast(allHitzonesAffected.Get(hitZone));
			}
				
			radiationDamage.AddRadiationAreas(GetParent());
		}
	}
	
	//------------------------------------------------------------------------------------------------
	//! Callback when an entity exits this DamageArea this frame
	//! \param[in] entity
	override void OnAreaExit(IEntity entity)
	{
		SCR_ExtendedDamageManagerComponent damageManagerExt = SCR_ExtendedDamageManagerComponent.Cast(SCR_DamageManagerComponent.GetDamageManager(entity));
		if (!damageManagerExt)
			return;
		
		array<HitZone> allHitZones = {};
		damageManagerExt.GetAllHitZones(allHitZones);
		 if (allHitZones.IsEmpty())
			return;
		
		array<ref SCR_PersistentDamageEffect> damageEffects = {};
		if (damageManagerExt.FindAllDamageEffectsOfType(GetDamageEffect().Type(), damageEffects) < 1)
			return;
		
		map<HitZone, SCR_PersistentDamageEffect> allHitzonesAffected = new map<HitZone, SCR_PersistentDamageEffect>();
		foreach (SCR_PersistentDamageEffect dmgEffect : damageEffects)
		{
			allHitzonesAffected.Insert(dmgEffect.GetAffectedHitZone(), dmgEffect);
		}
		
		foreach (HitZone hitZone : allHitZones)
		{
			RAD_RadiationDamageEffect radiationDamage;
			if (allHitzonesAffected.Contains(hitZone))
			{
				radiationDamage = RAD_RadiationDamageEffect.Cast(allHitzonesAffected.Get(hitZone));
				radiationDamage.RemoveRadiationArea(GetParent());
			}
		}
	}
	
	//------------------------------------------------------------------------------------------------
	float GetRadiationEmissionRate()
	{
		return m_fEmissionRate;
	}
}

modded enum EDamageType
{
	RADIATION,
}