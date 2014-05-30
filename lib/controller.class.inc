<?php


/**
* controller main class
*/
class controller
{
	
	/**
	 * rokfor DB Class
	 *
	 * @var object
	 **/
	var $rfDB;
	
	/**
	 * utilites
	 * 
	 * @var class
	 */
	var $u;
	
	/**
	 * html code
	 *
	 * @var string
	 **/
	var $html;
	
	
	/**
	 * domready javascript data
	 *
	 * @var string
	 **/
	var $domready;
	
	
	/**
	 * initial time stamp
	 *
	 * @var string
	 **/
	var $time;
	
	/**
	 * holding the active book object
	 *
	 * @var string
	 **/
	var $book;

	/**
	 * holding the active issue object
	 *
	 * @var string
	 **/
	var $issue;

	/**
	 * holding the active chapter object
	 *
	 * @var string
	 **/
	var $chapter;


	/**
	 * holding the active element object
	 *
	 * @var string
	 **/
	var $element;
	
	
	/**
	 * holding the data tree
	 *
	 * @var string
	 **/
	var $tree;

	/**
	 * constructor
	 * 
	 * issue of the translation database
	 * @param int $translationIssue
	 * 	
	 * if true prints the doctype, html and body tags before and after the end of the html stack
	 * default: false (suitable for ajax output)
	 * @param bool $doctype
	 *
	 * normally, only entries starting with the filter character are eligible
	 * for return translation.
	 * @param string $filter	
	 *
	 * @return void
	 * @author Urs Hofer
	 **/
	function __construct()
	{
		mb_internal_encoding("UTF-8");
		$this->time = microtime(true);
		$this->html = "";
		$this->domready = array();
		require_once(SYSDIR.'/rokfor_DB.inc');
		$this->rfDB = new rokfor_DB();

		/* Load Default Selections */
		
		$this->_checkBook($_GET['book']);
		$this->_checkIssue($_GET['issue']);
		$this->_checkChapter($_GET['chapter']);		
		$this->_checkElement($_GET['element']);		
		$this->_loadData();


		/**
		 * Create output depending on the controller state
		 * No Controller: Print Start Template
		 * Ajax Controller: Load ajax template based upon the template id sent by GET
		 * Regular Controller: Load Template based upon the chapter id
		 */
	
		if (file_exists(template_path.'/chapters/'.$_GET['Controller'].'.phtml')) {
			$this->content('/chapters/'.$_GET['Controller'].'.phtml');						
		}
		else {
			$this->warning('Template does not exist. Falling back to the default view.');
			$this->content('default.phtml');			
		}
	}
	
	
	/**
	 * checks if a book is available and stores the book object
	 *
	 * @param string $_book 
	 * @return void
	 * @author Urs Hofer
	 **/
	function _checkBook($_book)
	{
		$_newid = false;
		$this->tree->books = $this->rfDB->getProjects(true);
		foreach ($this->tree->books as $_b) {
			if ($_b->_name==$_book) {
				$this->book = $_b; 
				return;
			}
			if (!$_newid) $_newid = $_b;
		}
		if ($_book) $this->error("Book Id not found");
		$this->book = $_newid;
	}
	
	
	/**
	 * checks if an issue is available and stores the issue object
	 *
	 * @param string $_issue 
	 * @return void
	 * @author Urs Hofer
	 */
	function _checkIssue($_issue){
		if (!$this->book->id) $this->error("Book Id not set");
		$_newid = false;		
		$this->tree->issues = $this->rfDB->getEditions ($this->book->id, true);
		foreach ($this->tree->issues as $_e) {
			if ($_e->_name==$_issue) {
				$this->issue = $_e; 
				return;
			}
			if (!$_newid) $_newid = $_e;			
		}
		if ($_issue) $this->error("Issue Id not found");
		$this->issue = $_newid; 		
	}
	
	
	/**
	 * checks if an chapter is available and stores the chapter object
	 *
	 * @param string $_issue 
	 * @return void
	 * @author Urs Hofer
	 */
	function _checkChapter($_chapter){
		if (!$this->book->id) $this->error("Book Id not set");
		$_newid = false;		
		$this->tree->chapters = $this->rfDB->getParts($this->book->id, true);
		foreach ($this->tree->chapters as $_c) {
			if ($_c->_name==$_chapter) {
				$this->chapter = $_c; 
				return;
			}
			if (!$_newid) $_newid = $_c;			
		}
		if ($_chapter) $this->error("Chapter Id not found");		
		$this->chapter = $_newid; 		
	}	
	
	
	/**
	 * checks if an chapter is available and stores the chapter object
	 *
	 * @param string $_issue 
	 * @return void
	 * @author Urs Hofer
	 */
	function _checkElement($_element){
		if (!$this->issue->id) $this->error("Issue Id not set");
		$_newid = false;		
		$this->tree->elements = $this->rfDB->getElementsByIssue ($this->issue->id, 'close', false, $this->chapter->id);
		foreach ($this->tree->elements as $_e) {
			if ($_e->_name==$_element) {
				$this->element = $_e; 
				return;
			}
			if (!$_newid) $_newid = $_e;			
		}
		if ($_element) $this->error("Element Id not found");				
		$this->element = $_newid; 		
	}	
	
	
	
	/**
	 * loads the data of the current element
	 * if $_element is set, loads the data of the element with the specified id
	 * This can be used, to populate more than only one template, i.e. for lists.
	 *
	 * @param string $_element
	 * @return void
	 * @author Urs Hofer
	 */
	function _loadData($_element = false){
		if (!$_element) {
			if (!$this->element->id) $this->error("Element Id not set");
			$_element = $this->element->id;
		}
		$this->data = $this->rfDB->getFieldsId($this->element->id);
	}	
	

	/**
	 * special char save urlencode function
	 *
	 * @param string $string 
	 * @return void
	 * @author Urs Hofer
	 */
	function urlencode($string) 
	{
	    return urlencode($string);
	    $entities = array('%21', '%2A', '%27', '%28', '%29', '%3B', '%3A', '%40', '%26', '%3D', '%2B', '%24', '%2C', '%2F', '%3F', '%25', '%23', '%5B', '%5D');
	    $replacements = array('!', '*', "'", "(", ")", ";", ":", "@", "&", "=", "+", "$", ",", "/", "?", "%", "#", "[", "]");
	    return str_replace($replacements, $entities,urlencode($string));
	}

	/**
	 * Render a template file and adding the output to the stack
	 * Within a template file, all constructions like <?=$func?>
	 * are substituted with the return result of a function in $this class
	 * called $func.
	 *
	 * @param string $_file 
	 * @return void
	 * @author Urs Hofer
	 */
	private function __render($_file)
	{
		// 1. Get all required fields out of the template
		$_tpl = array();
		if (!$_source = @file_get_contents(template_path.'/'.$_file))
			throw new Exception("Template $_file not found", 1);
		preg_match_all('/\<\?=\$(.*?)\?>/', $_source, $_tpl);
		foreach (array_unique($_tpl[1]) as $_renderer) {
			if (method_exists($this, $_renderer)) {
				try {
					$$_renderer = $this->$_renderer();
				} catch (Exception $e) {
					$this->error($e->getMessage());
				}
			}
			else $$_renderer = view_missing.":".$_renderer;
		}


	    ob_start();
	    require template_path.'/'.$_file;
	    $this->addHTML(ob_get_clean());	
	}

	/**
 	 * adding HTML to the Stack
	 *
	 * @param string $_code 
	 * @return void
	 * @author Urs Hofer
	 */
	function addHTML($_code) 
	{
		$this->html .= $_code;		
	}


	/**
	 * adding Javascript code to the domready Stack
	 *
	 * @param string $_code 
	 * @return void
	 * @author Urs Hofer
	 */
	function addDomready($_code) 
	{
		$this->domready[] = $_code;		
	}


	/**
	 * renders the content of a template file
	 *
	 * @param string $_file
	 * @return void
	 * @author Urs Hofer
	 **/
	function content($_file)
	{
		try {
			$this->__render($_file);
		} catch (Exception $e) {
			$this->error($e->getMessage());
		}
	}

	/**
	 * error: prints an error message with a http 404 header
	 * the script will be terminated immediately afterwards.
	 *
	 * @param string $msg 
	 * @param string $template 
	 * @return void
	 * @author Urs Hofer
	 */
	function error($msg,$template='sys/404.phtml')
	{
		header("HTTP/1.0 404 Not Found");
	    require template_path.'/'.$template;
		die();
	}
	
	/**
	 * waring: dumps a commented warning
	 *
	 * @param string $msg 
	 * @return void
	 * @author Urs Hofer
	 */
	function warning($msg)
	{
		$this->addHTML('
<!-- '.$msg.' -->
');
	}	
	
	/**
	 * dump: echoing html and domready javascript
	 *
	 * @return void
	 * @author Urs Hofer
	 */
	function dump($echo = true) 
	{
		if (count($this->domready)>0) {
			$this->addHTML('<script type="text/javascript" charset="utf-8">
			window.addEvent(\'domready\', function() {
				'.join("\n",$this->domready).'
				});
			</script>');
		}
		if ($this->doctype) $this->addHTML('</body></html>');
        if ($echo) {
			echo ($this->html);
		}
		else {
			return ($this->html);
		}
	}
	
	/**
	 * returns the time used so far
	 *
	 * @return int
	 * @author Urs Hofer
	 **/
	function getRendertime() 
	{
		echo (round(microtime(true) - $this->time,4). " s.");
	}

}


?>
