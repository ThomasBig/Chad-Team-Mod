[BaseContainerProps(configRoot: true)]
class SCR_RadiationAttributes
{
	[Attribute()]
	protected ref array<ref SCR_RadiationAttribute> m_aAttributes;
	
}

[BaseContainerProps(configRoot: true)]
class SCR_RadiationAttribute
{
	[Attribute()]
	protected float m_fDistance;
	
	[Attribute(params: "gamemat")]
	protected ResourceName m_sMaterial;
	
	[Attribute()]
	protected float m_fRadiationFactor;
}