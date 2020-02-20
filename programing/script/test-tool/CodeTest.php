<?php
Class CodeTest{
  public $name;
  public function __construct($name = '名無し'){
     $this->name = $name;    
  }
  
  public function morning(){
      echo $this->name."さん、おはようございます。";
  }
  public function daytime(){
      echo "こんにちは!!".$this->name."さん";
  }
  public function night(){
      echo $this->name."さん、こんばんはー。";
  }
  public function goodNignt(){
      echo $this->name."さん、おやすみなさい";
  }
}
?>
