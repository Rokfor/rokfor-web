<?php
	/**
	 * Initialize Session
	 */

	ini_set('display_errors','Off');

	/**
	 * Include Libraries
	 */

    require_once(dirname(__FILE__).'/../rf_config-v2.inc');
    require_once(dirname(__FILE__).'/local/view.class.inc');	

	/**
	 * Load Main Class
	 */

	$s = new view();

	/**
	 * Dump HTML
	 */

	$s->dump();

	/**
	 * Print Render Time
	 */
	
	$s->rendertime(); 
?>