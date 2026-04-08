#include "../base/stormc_random.c"

#define NEYIEH_PAGES 26
#define MAX_PARAGRAPHS 32




struct neiyeh_page {
	u64			page_number;
	u64			paragraphs[MAX_PARAGRAPHS];
	struct stc_string8	paragraph_text[MAX_PARAGRAPHS];
	u64			ct_paragraphs;
};
struct neiyeh {
	struct neiyeh_page	pages[NEYIEH_PAGES];
	u64			ct_pages;
};


static struct neiyeh neiyeh = {
	.pages = {
		[0] = {
			.page_number = 0,
			.paragraph_text = {
				[0]	= STR("The vital essence of all things:"),
				[1]	= STR("It is this that brings them to life."),
				[2]	= STR("It generates the five grains below"),
				[3]	= STR("And becomes the constellated stars above"),
				[4]	= STR("When flowing amid the heavens and the earth"),
				[5]	= STR("We call it ghostly and numinous"),
				[6]	= STR("When stored within the chests of human beings"),
				[7]	= STR("We call them sages"),
			},
			.ct_paragraphs = 8,
		},
		[1] = {
			.page_number = 1,
			.paragraph_text = {
				[0]	= STR("Therefore this vital energy is:"),
				[1]	= STR("Bright! -- as if ascending the heavens;"),
				[2]	= STR("Dark! -- as if entering an abyss;"),
				[3]	= STR("Vast! -- as if dwelling in an ocean;"),
				[4]	= STR("Lofty! -- as if dwelling on a mountain peak."),
				[5]	= STR("Therefore this vital energy"),
				[6]	= STR("Cannot be halted by force,"),
				[7]	= STR("Yet can be secured by inner power [Te]."),
				[8]	= STR("Cannot be summoned by speech,"),
				[9]	= STR("Yet can be  welcomed by the awareness."),
				[10]	= STR("Reverently hold onto it and do not lose it:"),
				[11]	= STR("This is called \"developing inner power\"."),
				[12]	= STR("When inner power develops and wisdom emerges,"),
				[13]	= STR("The myriad things will, to the last one, be grasped."),
			},
			.ct_paragraphs = 14
		},
		[2] = {
			.page_number = 2,
			.paragraph_text = {
				[0]	= STR("All the forms of the mind"),
				[1]	= STR("Are naturally infused and filled with it [the vital essence],"),
				[2]	= STR("Are naturally generated and developed [because of] it."),
				[3]	= STR("It is lost."),
				[4]	= STR("Inevitably because of sorrow, happiness, joy, anger, desire, and profit seeking."),
				[5]	= STR("If you are able to cast off sorrow, happiness, joy, anger, desire, and profit seeking."),
				[6]	= STR("Your mind will just revert to equanimity."),
				[7]	= STR("The true Condition of the mind"),
				[8]	= STR("Is that it finds calmness beneficial and, by it, attains repose."),
				[9]	= STR("Do not disturb it, do not disrupt it"),
				[10]	= STR("And harmony will naturally develop."),
			},
			.ct_paragraphs = 11,
		},
		[3] = {
			.page_number = 3,
			.paragraph_text = {
				[0]	= STR("Clear! as though right by yourside."),
				[1]	= STR("Vague! as though it will not be attained."),
				[2]	= STR("Indiscernable! as though beyond the limitless."),
				[3]	= STR("The test of this is not far off:"),
				[4]	= STR("Daily we make use of its inner power"),
				[5]	= STR("The Way is what infuses the body,"),
				[6]	= STR("Yet people are unable to fix it in place."),
				[7]	= STR("It goes forth but does not return,"),
				[8]	= STR("It comes back but does not stay,"),
				[9]	= STR("Silent! none can hear its sound."),
				[10]	= STR("Suddenly stopping! it abides within the mind."),
				[11]	= STR("Obscure! we do not see its form."),
				[12]	= STR("Surging forth! it arises with us."),
				[13]	= STR("We do not see its form"),
				[14]	= STR("We do not hear its sound"),
				[15]	= STR("Yet we can perceive an order to its accomplishments."),
				[16]	= STR("We call it \"the Way\"")
			},
			.ct_paragraphs = 17,
		},
		[4] = {
			.page_number = 4,
			.paragraph_text = {
				[0]	= STR("The Way has no fixed position:"),
				[1]	= STR("It abides within the excellent mind."),
				[2]	= STR("When the mind is tranquil and the vital breath is regular,"),
				[3]	= STR("The Way can thereby be halted."),
				[4]	= STR("The Way is not distant from us."),
				[5]	= STR("When people attain it they are sustained"),
				[6]	= STR("The Way is not separated from us;"),
				[7]	= STR("When people accord with it they are harmonious."),
				[8]	= STR("Therefore: Concentrated! as though you could be roped together with it."),
				[9]	= STR("Indiscernable! as though beyond all locations."),
				[10]	= STR("The true state of that Way:"),
				[11]	= STR("How could it be conceived of and pronounced upon?"),
				[12]	= STR("Cultivate your mind, make your thoughts tranquil,"),
				[13]	= STR("And the Way can thereby be attained."),
			},
			.ct_paragraphs = 14
		},
		[5] = {
			.page_number = 5,
			.paragraph_text = {
				[0]	= STR("As for the Way:"),
				[1]	= STR("It is what the mouth cannot speak of;"),
				[2]	= STR("The eyes cannot see"),
				[3]	= STR("And the ears cannot hear."),
				[4]	= STR("It is that with which we cultivate the mind and laign the body."),
				[5]	= STR("When people lose it they die;"),
				[6]	= STR("When people attain it the flourish."),
				[7]	= STR("When endeavors lose it they fail;"),
				[8]	= STR("When they gain it they succeed."),
				[9]	= STR("The way never has root or trunk"),
				[10]	= STR("It never has leaves or flowers."),
				[11]	= STR("The myriad things are generated by it."),
				[12]	= STR("The myriad things are completed by it."),
				[13]	= STR("We designate it \"the Way\"."),
			},
			.ct_paragraphs = 14
		},
		[6] = {
			.page_number = 6,
			.paragraph_text = {
				[0]	= STR("For the heavens, the ruling principle is to be aligned."),
				[1]	= STR("For the earth, the ruling principle is to be level."),
				[2]	= STR("For human beings the ruling principle is to be tranquil."),
				[3]	= STR("Spring, autumn, winter, and summer are the seasions of the heavens."),
				[4]	= STR("Mountains, hills, rivers, and valleys are the resources of the earth."),
				[5]	= STR("Pleasure and anger, accepting and rejecting are the devices of human beings."),
				[6]	= STR("Therefore the Sage:"),
				[7]	= STR("Alters with the seaons but doesn't transform,"),
				[8]	= STR("Shifts with things but doesn't change places with them."),
			},
			.ct_paragraphs = 9
		},
		[7] = {
			.page_number = 7,
			.paragraph_text = {
				[0]	= STR("If you can be aligned and be tranquil,"),
				[1]	= STR("Only then can you be stable"),
				[2]	= STR("With a stable mind at your core"),
				[3]	= STR("With the eyes and ears acute and clear,"),
				[4]	= STR("And with the four limbs firm and fixed,"),
				[5]	= STR("You can thereby make a lodging place for the vital essence."),
				[6]	= STR("The vital essence: it is the essence of the vital energy."),
				[7]	= STR("When the vital energy is guided, it [the vital essence] is generated."),
				[8]	= STR("But when it is generated, there is thought,"),
				[9]	= STR("When there is thought, ther eis knowledge,"),
				[10]	= STR("But when there is knowledge, then you must stop."),
				[11]	= STR("Whenever the forms of the mind have excessive knowledge,"),
				[12]	= STR("You lose your vitality."),
			},
			.ct_paragraphs = 13
		},

		[8] = {
			.page_number = 8,
			.paragraph_text = {
				[0]	= STR("Those who can transform even a single ting, call them \"numinous\";"),
				[1]	= STR("Those who can alter even a single situation, call them \"wise\";"),
				[2]	= STR("But to transform without expanding vital energy, to alter without expanding wisdom:"),
				[3]	= STR("Only exemplary persons who hold fast to the One are able to do this."),
				[4]	= STR("Hold fast to the One, do not lose it,"),
				[5]	= STR("And you will be able to master the myriad things."),
				[6]	= STR("Exemplary persons act upon things,"),
				[7]	= STR("And are not acted upon by them,"),
				[8]	= STR("Because they grasp the guiding principle of the One."),
			},
			.ct_paragraphs = 9
		},

		[9] = {
			.page_number = 9,
			.paragraph_text = {
				[0]	= STR("With a well-ordered mind within you,"),
				[1]	= STR("Well-ordered words issue forth from your mouth,"),
				[2]	= STR("And well-ordered tasks are imposed upon others."),
				[3]	= STR("Then all under the heavens will be well ordered."),
				[4]	= STR("When one word is grasped,"),
				[5]	= STR("All under the heavens will submit."),
				[6]	= STR("When one word is fixed,"),
				[7]	= STR("All under the heavens will listen."),
				[8]	= STR("It is this [word \"Way\"] to which the saying refers."),
			},
			.ct_paragraphs = 9
		},
		[10] = {
			.page_number = 10,
			.paragraph_text = {
				[0]	= STR("When your body is not aligned,"),
				[1]	= STR("The inner power power will not come."),
				[2]	= STR("When you are not tranquil within,"),
				[3]	= STR("Your mind will not be well ordered."),
				[4]	= STR("Align  your body, assist the inner power,"),
				[5]	= STR("Then it will gradually come on its own."),
			},
			.ct_paragraphs = 6
		},
		[11] = {
			.page_number = 11,
			.paragraph_text = {
				[0]	= STR("The numinous [mind]: no one knows its limit;"),
				[1]	= STR("It intuitively knows the myriad things."),
				[2]	= STR("Hold it within you, do not let it waver."),
				[3]	= STR("To not disrupt your senses with external things"),
				[4]	= STR("To not disrupt your mind with your senses:"),
				[5]	= STR("This is called \"grasping it within you\"."),
			},
			.ct_paragraphs = 6
		},
		[12] = {
			.page_number = 12,
			.paragraph_text = {
				[0]	= STR("There is a numinous [mind] naturally residing within;"),
				[1]	= STR("One moment it goes, the next it comes,"),
				[2]	= STR("And no one is able to conceive of it."),
				[3]	= STR("If you lose it you are inevitably disordered."),
				[4]	= STR("If you attain it you are inevitably well ordered."),
				[5]	= STR("Diligently clean out its lodging place."),
				[6]	= STR("And its vital essence will naturally arrive."),
				[7]	= STR("Still your attempts to imagine and conceive of it."),
				[8]	= STR("Relax your efforts to reflect on and control it."),
				[9]	= STR("Be reverent and diligent."),
				[10]	= STR("And its vital essence will naturally stabilize."),
				[11]	= STR("Grasp it and don't let go."),
				[12]	= STR("Then the eyes and ears won't overflow."),
				[13]	= STR("And the mind will have nothing else to seek."),
				[14]	= STR("When a properly aligned mind resides within you,"),
				[15]	= STR("The myriad things will be seen in their proper perspective."),
			},
			.ct_paragraphs = 16
		},
		[13] = {
			.page_number = 13,
			.paragraph_text = {
				[0]	= STR("The way fills the entire world."),
				[1]	= STR("It is everywhere where people are."),
				[2]	= STR("But people are unable to understand this."),
				[3]	= STR("When you are released by this one word:"),
				[4]	= STR("You reach up to the heavens above;"),
				[5]	= STR("You stretch down to the earth below;"),
				[6]	= STR("You pervade the nine inhabited regions."),
				[7]	= STR("What does it mean to be released by it?"),
				[8]	= STR("The answer resides in the calmness of the mind."),
				[9]	= STR("When your mind is well ordered, your senses are well ordered."),
				[10]	= STR("When  your mind is calm, your senses are calmed."),
				[11]	= STR("What makes them well ordered is the mind;"),
				[12]	= STR("What makes them calm is the mind."),
				[13]	= STR("By means of the mind you store the mind."),
				[14]	= STR("Within the mind there is another mind."),
				[15]	= STR("That mind within the mind, it is an awareness the precedes words."),
				[16]	= STR("Only after there is awareness does it take shape."),
				[17]	= STR("Only after it takes shape is there a word."),
				[18]	= STR("Only after ther eis a word it is implemented."),
				[19]	= STR("Only after it is implemented is there order."),
				[20]	= STR("Without order, you will always be chaotic."),
				[21]	= STR("If chaotic, you die."),
			},
			.ct_paragraphs = 22
		},
		[14] = {
			.page_number = 14,
			.paragraph_text = {
				[0]	= STR("For those who preserve and naturally generate vital essence"),
				[1]	= STR("On the outside a calmness will flourish."),
				[2]	= STR("Stored inside, we take it to be the well spring."),
				[3]	= STR("Floodlike, it harmoinzes and equalizes"),
				[4]	= STR("And we take it to be the fount of the vital energy."),
				[5]	= STR("When the fount is not dried up,"),
				[6]	= STR("The four limbs are firm."),
				[7]	= STR("When the well spring is not drained."),
				[8]	= STR("Vital energy freely circulates through the nine apertures."),
				[9]	= STR("You can then exhaust the heavens and the earth."),
				[10]	= STR("And spread over the four seas."),
				[11]	= STR("When  you have no delusions within you."),
				[12]	= STR("Externally there will be no disasters."),
				[13]	= STR("Those who keep their minds unimpared within,"),
				[14]	= STR("Externally keep their bodies unimpared,"),
				[15]	= STR("Who do not encounter heavenly disasters,"),
				[16]	= STR("Or meet with harm at the hands of otheres,"),
				[17]	= STR("Call them Sages.")
			},
			.ct_paragraphs = 18
		},
		[15] = {
			.page_number = 15,
			.paragraph_text = {
				[0]	= STR("If people can be aligned and tranquil,"),
				[1]	= STR("Their skin will be ample and smooth,"),
				[2]	= STR("Their ears and eyes will be acute and clear,"),
				[3]	= STR("Their muscles will be suppler and their bones will be strong."),
				[4]	= STR("They will then be able to hold up the Great Circle [of the heavens]"),
				[5]	= STR("And tread firmly over the Great Square [of the earth]."),
				[6]	= STR("They will mirror things with great purity."),
				[7]	= STR("And will perceive things with great clarity."),
				[8]	= STR("Reverently be aware [of the Way] and do not waver,"),
				[9]	= STR("And you will daily renew your inner power."),
				[10]	= STR("Thoroughly understand all under the heavens."),
				[11]	= STR("And exhaust everything within the Four Directions."),
				[12]	= STR("To reverently bring forth the effulgence [of the Way]:"),
				[13]	= STR("This is called \"inward attainment\"."),
				[14]	= STR("If you do this but fail to return to it, "),
				[15]	= STR("This will cause a wavering in your vitality."),
			},
			.ct_paragraphs = 16
		},
		[16] = {
			.page_number = 16,
			.paragraph_text = {
				[0]	= STR("For all [to practice] this Way:"),
				[1]	= STR("You must uncoil, you must expand,"),
				[2]	= STR("You must be firm, you must be regular [in this practice]."),
				[3]	= STR("Hold fast to this excellent [practice]; do not let go of it."),
				[4]	= STR("Chase away the excessive; abandon the trivial,"),
				[5]	= STR("And when you reach its ultimate limit"),
				[6]	= STR("You will return to the Way and its inner power."),
			},
			.ct_paragraphs = 7
		},
		[17] = {
			.page_number = 17,
			.paragraph_text = {
				[0]	= STR("When there is a mind that is unimpared within you,"),
				[1]	= STR("It cannot be hidden,"),
				[2]	= STR("It will be known in your countenance,"),
				[3]	= STR("And seen in your skin color."),
				[4]	= STR("If with this good flow of vital energy you encounter others,"),
				[5]	= STR("They will be kinder to you than your own brethren."),
				[6]	= STR("But if with a bad flow of vital energy you encounter others,"),
				[7]	= STR("They will harm you with their weapons."),
				[8]	= STR("[This is because] the wordless pronouncement"),
				[9]	= STR("Is more rapid than the drumming of thunder."),
				[10]	= STR("The perceptible form of the mind's vital energy"),
				[11]	= STR("Is brighter than the sun and moon,"),
				[12]	= STR("And more apparent than the concern of parents."),
				[13]	= STR("Rewards are not sufficient to encourage the good."),
				[14]	= STR("Punishments are not sufficient to discourage the bad."),
				[15]	= STR("Yet once this flow of vital energy is achieved,"),
				[16]	= STR("All under the heavens will submit,"),
				[17]	= STR("And once the mind is made stable,"),
				[18]	= STR("All under the heavens will listen."),
			},
			.ct_paragraphs = 19
		},
		[18] = {
			.page_number = 18,
			.paragraph_text = {
				[0]	= STR("By concentrating your vital breath as numinous"),
				[1]	= STR("The myriad things will all be contained within you."),
				[2]	= STR("Can you concentrate? Can you unite with them?"),
				[3]	= STR("Can you not resort to divining by tortoise or milfoil"),
				[4]	= STR("Yet know bad and good fortune?"),
				[5]	= STR("Can  you stop? Can you cease?"),
				[6]	= STR("Can you not seek it in others,"),
				[7]	= STR("Yet attain it in yourself?"),
				[8]	= STR("You think and think about it"),
				[9]	= STR("And think still further about it"),
				[10]	= STR("You think, yet still cannot penetrate it"),
				[11]	= STR("While the ghostly and numinous will penetrate it."),
				[12]	= STR("It is not due to the power of the ghostly and numinous,"),
				[13]	= STR("But to the utmost refinement of your essential vital breath"),
				[14]	= STR("When the four limbs are aligned"),
				[15]	= STR("And the blood and vital breath are tranquil,"),
				[16]	= STR("Unify your awareness, concentrate your mind,"),
				[17]	= STR("Then your eyes and ears will not be overstimulated"),
				[18]	= STR("And even the far-off will sseem close at hand."),
			},
			.ct_paragraphs = 19
		},
		[19] = {
			.page_number = 19,
			.paragraph_text = {
				[0]	= STR("Deep thinking generates knowledge,"),
				[1]	= STR("Idleness and carelesness generate worry."),
				[2]	= STR("Cruelty and arrogance generate resentment."),
				[3]	= STR("Worry and grief generate illness."),
				[4]	= STR("When illness reaches a distressing degree, you die."),
				[5]	= STR("When you think about something and don't let go of it,"),
				[6]	= STR("Internally you will be distressed, externally you will be weak."),
				[7]	= STR("Do not plan things out in advance"),
				[8]	= STR("Or else your vitality will cede its dwelling."),
				[9]	= STR("In eating, it is best not to fill up;"),
				[10]	= STR("In thinking, it is best not ot overdo,"),
				[11]	= STR("Limit these to the appropriate degree"),
				[12]	= STR("And you will naturally reach it [vitality]."),
			},
			.ct_paragraphs = 13
		},
		[20] = {
			.page_number = 20,
			.paragraph_text = {
				[0]	= STR("As for the life of all human beings:"),
				[1]	= STR("The heavens bring forth their vital essence,"),
				[2]	= STR("The earth brings forth their bodies."),
				[3]	= STR("These two combine to make a person."),
				[4]	= STR("When they are in harmony, there is vitality."),
				[5]	= STR("When they are not in harmony, there is no vitality."),
				[6]	= STR("If we examine the Way of hramonizing them,"),
				[7]	= STR("Its essentials are not visible,"),
				[8]	= STR("Its signs are not numerous."),
				[9]	= STR("Just let a balanced and aligned [breathing] fill your chest"),
				[10]	= STR("And it will swirl and blend within your mind,"),
				[11]	= STR("This confers longevity."),
				[12]	= STR("When joy and anger are not limited,"),
				[13]	= STR("You should make a plan [to limit them]."),
				[14]	= STR("Restrict the five sense-desires;"),
				[15]	= STR("Cast away tese dual misfortunes."),
				[16]	= STR("Be not joyous, be not angry,"),
				[17]	= STR("Just let a balanced and aligned [breathing] fill your chest."),
			},
			.ct_paragraphs = 18
		},
		[21] = {
			.page_number = 21,
			.paragraph_text = {
				[0]	= STR("As for the vitality of all human beings"),
				[1]	= STR("It inevitably occurs because of balanced and aligned [breathing]."),
				[2]	= STR("The reason for its loss"),
				[3]	= STR("Is inevitably pleasure and anger, worry and anxiety."),
				[4]	= STR("Therefore, to bring your anger to a halt, there is nothing better than poetry;"),
				[5]	= STR("To cast off worry there is nothing better than music;"),
				[6]	= STR("To limit music there is nothing better than the rites;"),
				[7]	= STR("To hold onto the rites there is nothing better than reverence;"),
				[8]	= STR("To hold onto reverence there is nothing better than tranquility."),
				[9]	= STR("When you are inwardly tranquil and outwardly reverent"),
				[10]	= STR("You are able to return to your innate nature"),
				[11]	= STR("And this nature will become greatly stable."),
			},
			.ct_paragraphs = 12
		},
		[22] = {
			.page_number = 22,
			.paragraph_text = {
				[0]	= STR("For all the way of eating is that:"),
				[1]	= STR("Overfilling yourself with food will impair your vital energy"),
				[2]	= STR("And cause your body to deteriorate."),
				[3]	= STR("Overrestricting your consumption causes your bones to wither,"),
				[4]	= STR("And the blood to congeal."),
				[5]	= STR("The mean between overfilling and overrestricting:"),
				[6]	= STR("This is called \"harmonious completion\"."),
				[7]	= STR("It is where the vital essence lodges."),
				[8]	= STR("And knowledge is generated."),
				[9]	= STR("When hunger and fullness lose their proper balance,"),
				[10]	= STR("You make a plan to correct this."),
				[11]	= STR("When full, move quickly,"),
				[12]	= STR("When hungry, neglect your thoughts;"),
				[13]	= STR("When old, forget worry."),
				[14]	= STR("If when full you don't move quickly,"),
				[15]	= STR("Vital energy will not circulate to your limbs."),
				[16]	= STR("If when hungry you don't neglect thoughts of food,"),
				[17]	= STR("When you finally eat you will not stop."),
				[18]	= STR("If when old you don't forget your worries,"),
				[19]	= STR("The fount of your vital energy will rapidly drain out."),
			},
			.ct_paragraphs = 20
		},
		[23] = {
			.page_number = 23,
			.paragraph_text = {
				[0]	= STR("When you enlarge your mind and let go of it,"),
				[1]	= STR("When you relax your vital breath and expand it,"),
				[2]	= STR("When your body is calm and unmoving:"),
				[3]	= STR("And you can maintain the One and discard the myriad disturbances."),
				[4]	= STR("You will see profit and not be enticed by it,"),
				[5]	= STR("You will see harm and not be frightened by it,"),
				[6]	= STR("Relaxed and unwound, yet acutely sensitive,"),
				[7]	= STR("In solitude you delight in your own person."),
				[8]	= STR("This is called \"revolving the vital breath\"."),
				[9]	= STR("Your thoughts and deeds seem heavenly."),
			},
			.ct_paragraphs = 10
		},
		[24] = {
			.page_number = 24,
			.paragraph_text = {
				[0]	= STR("The vitality of all people"),
				[1]	= STR("Inevitably comes from their peace of mind."),
				[2]	= STR("When anxious, you lose this guiding thread."),
				[3]	= STR("When angry, you lose this basic point."),
				[4]	= STR("When you are anxious or sad, pleased or angry,"),
				[5]	= STR("The Way has no place within you to settle."),
				[6]	= STR("Love and desire: still them!"),
				[7]	= STR("Folly and disturbance: correct them!"),
				[8]	= STR("Do not push it! do not pull it!"),
				[9]	= STR("Good fortune will naturally return to you,"),
				[10]	= STR("And that Way will naturally come to you"),
				[11]	= STR("So you can rely on and take control from it."),
				[12]	= STR("If you are tranquil then you will attain it."),
				[13]	= STR("If you are agitated then you will lose it."),
			},
			.ct_paragraphs = 14
		},
		[25] = {
			.page_number = 25,
			.paragraph_text = {
				[0]	= STR("The mysterious vital energy within the mind:"),
				[1]	= STR("One moment it arrives, the next it departs."),
				[2]	= STR("So fine, there is nothing within it;"),
				[3]	= STR("So vast, there is nothing outside it."),
				[4]	= STR("We lose it"),
				[5]	= STR("Because of the harm caused by mental agitation."),
				[6]	= STR("When the mind can hold on to tranquility,"),
				[7]	= STR("The Way will become naturally stabilized."),
				[8]	= STR("For people who have attained the Way"),
				[9]	= STR("It permeates their pores and saturates their hair."),
				[10]	= STR("Within their chest, they remain unvanquished."),
				[11]	= STR("[Follow] this way of restricting sense-desires"),
				[12]	= STR("And the myriad things will not cause you harm."),
			},
			.ct_paragraphs = 13
		},
	},
	.ct_pages = 26,
};




static void neiyeh_viewall(void)
{
	for (u64 i = 0; i < neiyeh.ct_pages; ++i) {
		u64 paragraphs = neiyeh.pages[i].ct_paragraphs;
		for (u64 j = 0; j < paragraphs; ++j) {
			struct stc_string8 p = neiyeh.pages[i].paragraph_text[j];
			printf("[%lu] %s\n", j, p.str);
		}
	}
}


static void neiyeh_random(void)
{
	u64 idx = stc_random_range(0, neiyeh.ct_pages - 1);
	u64 paragraphs = neiyeh.pages[idx].ct_paragraphs;
	for (u64 j = 0; j < paragraphs; ++j) {
		struct stc_string8 p = neiyeh.pages[idx].paragraph_text[j];
		printf("[%lu] %s\n", j, p.str);
	}
}
