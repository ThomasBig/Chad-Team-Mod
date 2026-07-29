class SCR_Trace
{
	//------------------------------------------------------------------------------------------------
	//! Trace from entity to a given hitzone and gets all the traced entities
	//! \param[in] radiationPoint
	//! \param[in] player
	//! \param[in] hitzone
	//! \param[out] tracedEntities
	void TraceFromEntityToHitzone(notnull IEntity radiationPoint, notnull IEntity player, notnull HitZone hitzone, out array<IEntity> tracedEntities, out array<GameMaterial> tracedMaterials)
	{
		tracedEntities.Clear();
		
		vector outMat[4];
		int outBoneIndex, nodeId;
		hitzone.TryGetColliderDescription(player, -1, outMat, outBoneIndex, nodeId);
		
		GameMaterial material;
		IEntity tracedEntity = ExecuteTrace(radiationPoint, player, outMat[3], material);
		tracedMaterials.Insert(material);
		
		while (tracedEntity != null || tracedEntity != player)
		{
			tracedEntity = ExecuteTrace(tracedEntity, player, outMat[3], material);
			tracedEntities.Insert(tracedEntity);
			tracedMaterials.Insert(material);
		}
	}
	
	//------------------------------------------------------------------------------------------------
	protected IEntity ExecuteTrace(notnull IEntity entity, notnull IEntity player, vector hitzonePos, out GameMaterial material)
	{		
		TraceParam param = new TraceParam();
		param.Flags = TraceFlags.ENTS;
		param.LayerMask = EPhysicsLayerDefs.Projectile;
		param.Exclude = entity;
		param.Start = entity.GetOrigin();
		param.End = hitzonePos;
		
		World world = player.GetWorld();
		float traceDistance = world.TraceMove(param);
		if (traceDistance < 1)
		{
			Print(traceDistance);	
			material = param.SurfaceProps;
			return param.TraceEnt;
		}
		
		return null;
	}
}*/