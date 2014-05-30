<?php


/**
* View class: providing the data renderer for each field required in a template
* 
*  - The functions always have to be named according to the key in the $this->tpl - array
*  - For example: If the template base.phtml requires a field $this->tpl['info'], there must be a
*    method existing with the name info (always the array key with dots substituted by underlines)
* 
*/


require_once('../rf_config-v2.inc');
require_once('constants.local.inc');
require_once('../lib/controller.class.inc');

class view extends controller
{

	/**
	 * constructor: The constructor in the view subclass provides global variables which can be reused by
	 * the different renderer
	 *
	 * @return void
	 * @author Urs Hofer
	 **/
	function __construct() {
		parent::__construct(); 

	}

	/**
	 * Select all Chapters with at least some data in it of the Book "Webseite"
	 *
	 * @return string
	 * @author Urs Hofer
	 */
	function menu() {
		return ('<pre>'.print_r($this->tree,true).'</pre>');
	}



	/**
	 * list output of all contributions within a chapter sorted manually
	 *
 	 * @return void
	 * @author Urs Hofer
	 */
	function content() 
	{
		return ('<pre>'.print_r($this->data,true).'</pre>');
	}
}


?>
