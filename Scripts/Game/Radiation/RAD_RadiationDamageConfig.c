[BaseContainerProps()]
class RAD_RadiationDamageConfig : Managed
{
	[Attribute(defvalue: "300", desc: "[seconds] How long does it take to kill the character from full health when they have the radiation poisoning level of 1.")]
	float m_fTimeToKillPerPoisonLevel;
	
	[Attribute(defvalue: "300", desc: "[seconds] How long does it take for character to lose radiation poisoning level 1.")]
	float m_fTimeToCurePoisonLevel;
	
	[Attribute(defvalue: "0.017", desc: "How many radiation poison level does the character aquire per emition (per second) at 0 distance")]
	float m_fPoisonLevelPerEmition;
}