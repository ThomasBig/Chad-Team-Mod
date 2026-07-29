class SCR_Trace
{
	//------------------------------------------------------------------------------------------------
	//! Trace from entity to a given hitzone and gets all the traced entities
	//! \param[in] radiationPoint
	//! \param[in] player
	//! \param[in] hitzone
	//! \param[out] tracedEntities
	void TraceFromEntityToHitzone(notnull IEntity radiationPoint, notnull IEntity player, notnull HitZone hitzone, out array<IEntity> tracedEntities)
	{
		tracedEntities.Clear();
		
		vector outMat[4];
		int outBoneIndex, nodeId;
		hitzone.TryGetColliderDescription(player, -1, outMat, outBoneIndex, nodeId);
		
		IEntity tracedEntity = ExecuteTrace(radiationPoint, player, outMat[3]);
		
		while (tracedEntity != player || tracedEntity != null)
		{
			tracedEntity = ExecuteTrace(tracedEntity, player, outMat[3]);
			tracedEntities.Insert(tracedEntity);
		}
	}
	
	//------------------------------------------------------------------------------------------------
	protected IEntity ExecuteTrace(notnull IEntity entity, notnull IEntity player, notnull vector hitzonePos)
	{		
		TraceParam param = new TraceParam();
		param.Flags = TraceFlags.ENTS;
		param.LayerMask = EPhysicsLayerDefs.Projectile;
		param.Exclude = entity;
		param.Start = entity.GetOrigin();
		param.End = hitzonePos;
		
		World world = player.GetWorld();
		
		if (world.TraceMove(param) < 1)
			return param.TraceEnt;
		
		return null;
	}
}