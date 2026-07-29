class SCR_Trace
{
	//------------------------------------------------------------------------------------------------
	//! Trace from entity to a given hitzone and gets all the traced entities
	//! \param[in] radiationPoint
	//! \param[in] player
	//! \param[in] hitzone
	//! \param[out] tracedEntities
	void TraceFromEntityToEntity(notnull IEntity radiationPoint, notnull IEntity player, out array<IEntity> tracedEntities, out array<GameMaterial> tracedMaterials, out array<float> distances)
	{
		tracedEntities.Clear();
		
		SCR_CharacterDamageManagerComponent damageComp = SCR_CharacterDamageManagerComponent.Cast(player.FindComponent(SCR_CharacterDamageManagerComponent));
		
		GameMaterial material;
		float distance;
		vector playerPos = player.GetOrigin();
		IEntity tracedEntity;
		
		tracedEntity = ExecuteTrace(radiationPoint, playerPos, material, distance);
		if (!tracedEntity)
		{
			distances.Insert(distance);
			return;
		}
		
		tracedMaterials.Insert(material);

		while (tracedEntity != null)
		{
			tracedEntity = ExecuteTrace(tracedEntity, playerPos, material, distance);
			tracedEntities.Insert(tracedEntity);
			tracedMaterials.Insert(material);
			distances.Insert(distance);
		}
	}
	
	//------------------------------------------------------------------------------------------------
	protected IEntity ExecuteTrace(notnull IEntity entity, vector playerPos, out GameMaterial material, out float distance)
	{		
		TraceParam param = new TraceParam();
		param.Flags = TraceFlags.ENTS;
		param.LayerMask = EPhysicsLayerDefs.Projectile;
		param.Exclude = entity;
		param.Start = entity.GetOrigin();
		param.End = playerPos;
		
		World world = entity.GetWorld();
		distance = world.TraceMove(param);
		if (distance < 1)
		{
			material = param.SurfaceProps;
			return param.TraceEnt;
		}
		
		return null;
	}
}