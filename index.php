<?php
	/**
	 * Error Reporting: Disable for production mode
	 */

	error_reporting(E_ALL & ~E_NOTICE);
	// ini_set('display_errors','Off');

	/**
	 * Include Libraries
	 */

    require_once(dirname(__FILE__).'/../rf_config-v2.inc');

	/**
	 * Include Configuration
	 */

    require_once(dirname(__FILE__).'/local/view.class.inc');	

	/**
	 * Load Main Class
	 * 
	 * $s = new view(true) -> Using .jade templates
	 * $s = new view()     -> Using .phtml templates
	 * 
	 */

	$s = new view(true);

	/**
	 * Dump HTML
	 */

	$s->dump();

?>