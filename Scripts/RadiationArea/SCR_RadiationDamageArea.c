class SCR_RadiationDamageArea : SCR_DamageArea
{
	//------------------------------------------------------------------------------------------------
	//! Callback when an entity enters this DamageArea this frame
	//! \param[in] entity
	override void OnAreaEntered(notnull IEntity entity)
	{
		SCR_DamageManagerComponent damageManagerComp = SCR_DamageManagerComponent.Cast(entity.FindComponent(SCR_DamageManagerComponent));
		if (!damageManagerComp)
			return;
		
		array<HitZone> allHitZones = {};
		damageManagerComp.GetAllHitZones(allHitZones);
		 if (allHitZones.IsEmpty())
			return;
		
		bool effectApplied = IsEffectApplied(entity);
		
		foreach (HitZone hitZone : allHitZones)
		{
			
		}
	}
	
	//------------------------------------------------------------------------------------------------
	//! Callback when an entity exits this DamageArea this frame
	//! \param[in] entity
	override void OnAreaExit(IEntity entity)
	{
		super.OnAreaExit(entity);
		
		
	}
}