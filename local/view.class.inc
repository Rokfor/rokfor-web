<?php
if(!defined('ROK')) die('Direct access is not allowed');


/**
* View class: providing the data renderer for each field required in a template
* 
*  - The functions always have to be named according to the key in the $this->tpl - array
*  - For example: If the template base.phtml requires a field $this->tpl['info'], there must be a
*    method existing with the name info (always the array key with dots substituted by underlines)
* 
*/


require_once(dirname(__FILE__).'/constants.local.inc');
require_once(dirname(__FILE__).'/../lib/controller.class.inc');

class view extends controller
{

	/**
	 * constructor: The constructor in the view subclass provides global variables which can be reused by
	 * the different renderer
	 *
	 * @return void
	 * @author Urs Hofer
	 **/
	function __construct($jade = false) {
		parent::__construct($jade); 
	}

	/**
	 * Select all Chapters with at least some data in it of the Book "Webseite"
	 *
	 * @return string
	 * @author Urs Hofer
	 */
	function dump_menu() {
		return (print_r($this->tree,true));
	}

	/**
	 * list output of all contributions within a chapter sorted manually
	 *
 	 * @return void
	 * @author Urs Hofer
	 */
	function dump_content() 
	{
		return (print_r($this->data,true));
	}
	


	function texfield() 
	{
		return ($this->data['Textfield']);	// Wrap it in a tag and return it.
	}
}


?>
