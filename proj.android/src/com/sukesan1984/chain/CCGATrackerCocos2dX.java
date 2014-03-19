package com.sukesan1984.chain;

import org.cocos2dx.lib.Cocos2dxActivity;

import com.google.analytics.tracking.android.EasyTracker;
import com.google.analytics.tracking.android.Fields;
import com.google.analytics.tracking.android.GoogleAnalytics;
import com.google.analytics.tracking.android.MapBuilder;
import com.google.analytics.tracking.android.Tracker;

import android.os.Bundle;
import android.util.Log;

public class CCGATrackerCocos2dX extends Cocos2dxActivity{
	
	//private static CCGATrackerCocos2dX instance = null;
	//private CCGATrackerCocos2dX(){}
	
	//private static EasyTracker tracker = null;
	
	/*
	public static EasyTracker getTracker(){
		return tracker;
	}
	*/
	

	protected void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);		
	}
	
	public void onStart(){
		EasyTracker.getInstance(this).activityStart(this);
	}
	
	public void onStop(){
		
		EasyTracker.getInstance(this).activityStop(this);
	}
	
	//JNIから呼び出すメソッド
	public static void trackView(String view)
	{
		Log.d("view:%s", view);
		Tracker tracker = GoogleAnalytics.getInstance(getContext()).getTracker("UA-8468750-6");
		tracker.set(Fields.HIT_TYPE, "appview");
		tracker.set(Fields.SCREEN_NAME,  view);
		tracker.send(MapBuilder.createAppView().build());
	}
	
	public static void trackEvent(String category, String action, String label, int value)
	{
		Log.d("Event:%s", category);
		Tracker tracker = GoogleAnalytics.getInstance(getContext()).getTracker("UA-8468750-6");
		tracker.send(MapBuilder.createEvent(category, action, label, (long) value).build());
	}
}