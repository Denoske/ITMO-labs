SELECT "Character"."name" FROM "Character" 
JOIN "character_feats" ON "Character"."char_id" = "character_feats"."char_id"
JOIN "feats" ON "character_feats"."feat_id" = "feats"."feat_id"
JOIN "atmospheric_layer" ON "Character"."atmo_layer_id" = "atmospheric_layer"."atmo_layer_id"
WHERE ("Character"."height" = 160 OR "Character"."height" = 170 OR "Character"."height" = 180) 
AND ("Character"."name" LIKE '%a') 
AND (LENGTH("feat_description") <= 20)
AND ("density" BETWEEN 50 AND 80)
ORDER BY LENGTH("Character"."name") DESC;
