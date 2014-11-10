<?php
	/**
	 * Initialize Session
	 */

	//	ini_set('display_errors','Off');
	error_reporting(E_ALL & ~E_NOTICE);
		
	/**
	 * Include Libraries
	 */

    require_once(dirname(__FILE__).'/../rf_config-v2.inc');
    require_once(dirname(__FILE__).'/local/view.class.inc');	

	/**
	 * Load Main Class
	 * Passing a boolean value switches the Jade Preprocessor on or off
	 */

	$s = new view(true);

	/**
	 * Dump HTML
	 */

	$s->dump();

	/**
	 * Print Render Time
	 */
	
	$s->rendertime(); 
?>