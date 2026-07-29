
class SCR_RadiationDamageArea : SCR_DamageArea
{
	[Attribute()]
	float m_fEmissionRate;
	
	//------------------------------------------------------------------------------------------------
	//! \return
	override bool IsRegisteredAutomatically()
	{
		return true;
	}
	
	//------------------------------------------------------------------------------------------------
	//! Callback when an entity enters this DamageArea this frame
	//! \param[in] entity
	override void OnAreaEntered(notnull IEntity entity)
	{
		/*SCR_ExtendedDamageManagerComponent damageManagerExt = SCR_ExtendedDamageManagerComponent.Cast(SCR_DamageManagerComponent.GetDamageManager(entity));
		if (!damageManagerExt)
			return;
		
		array<HitZone> allHitZones = {};
		damageManagerExt.GetAllHitZones(allHitZones);
		 if (allHitZones.IsEmpty())
			return;
		
		array<ref SCR_PersistentDamageEffect> damageEffects = {};
		damageManager.FindAllDamageEffectsOfType(GetDamageEffect().Type(), damageEffects);
		
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
				radiationDamage.SetAffectedHitZone(hitZone);
				AddDamage(radiationDamage);
			}
			else
			{
				radiationDamage = allHitzonesAffected.Get(hitZone);
			}
				
			radiationDamage.AddRadiationAreas(GetOwner());
		}*/
	}
	
	//------------------------------------------------------------------------------------------------
	//! Callback when an entity exits this DamageArea this frame
	//! \param[in] entity
	override void OnAreaExit(IEntity entity)
	{
		/*SCR_ExtendedDamageManagerComponent damageManagerExt = SCR_ExtendedDamageManagerComponent.Cast(SCR_DamageManagerComponent.GetDamageManager(entity));
		if (!damageManagerExt)
			return;
		
		array<HitZone> allHitZones = {};
		damageManagerExt.GetAllHitZones(allHitZones);
		 if (allHitZones.IsEmpty())
			return;
		
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
			if (allHitzonesAffected.Contains(hitZone))
			{
				radiationDamage = allHitzonesAffected.Get(hitZone);
				radiationDamage.RemoveRadiationArea(GetOwner());
			}
		}*/
	}
	
	//------------------------------------------------------------------------------------------------
	float GetRadiationEmissionRate()
	{
		return m_fEmissionRate;
	}
}