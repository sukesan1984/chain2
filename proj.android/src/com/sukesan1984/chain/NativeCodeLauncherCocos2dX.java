package com.sukesan1984.chain;
import jp.basicinc.gamefeat.ranking.android.sdk.controller.GFRankingController;

import org.cocos2dx.lib.Cocos2dxActivity;

import android.os.Bundle;


public class NativeCodeLauncherCocos2dX extends Cocos2dxActivity{
	protected void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);		
	}
	
	public static void showRanking(){
		GFRankingController.show(getContext(), "561");
	}
	
	public static void postHighScore(int kind, int score){
		//ƒXƒRƒA‚¾‚¯‘—‚é
		if(kind != 1){
			return;
		}
		
		String[] gameIds = {"561"};
		String[] scores = {Integer.toString(score)};
		GFRankingController appController = GFRankingController.getIncetance(getContext());
		appController.sendScore(gameIds, scores);
	}
	
}
