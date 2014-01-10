class HomeController < ApplicationController
  #VPN_Server = "http://192.168.1.11:3000/"
  #Raspberry_Openhab = "http://ensirasp:8080/rest/items/"
  Raspberry_Openhab = "http://192.168.42.1:8080/rest/items/"
  PROFESSOR_MACS = {
    "00:00:00:00:00:00" => {id: 1, name: "Frank Herbert"},
    "08:78:98:01:39:45" => {name: "Daniel Totoro"},
    "cc:f3:a5:32:a4:f9" => {name: "Medhi"}
  }
  
  @@active_stream = false
  
  def index
    
  end
  
  def mouvement
    #RestClient.get(VPN_Server+"mouvement")
    RestClient.put Raspberry_Openhab+'Mouvement_Detector/state', "ON", {:content_type => 'text/plain'}
  end
  
  def scantag
    #RestClient.get(VPN_Server+"professor")
    
    @mac = params[:mac]
    @professor = PROFESSOR_MACS[@mac]
    if @professor
      if @professor[:id]
        @presence_adr = Raspberry_Openhab+'Professor_Presence_'+@professor[:id].to_s+'/state'
      else
        # Normalement inutile à terme
        @presence_adr = Raspberry_Openhab+'Professor_Presence/state'
      end
      RestClient.put @presence_adr, "ON", {:content_type => 'text/plain'}
    else
      # Mac adress isn't recognized, it's not a professor but a student
      render :json => "https://www.google.com/calendar/render?pli=1" # TODO : Set the calendar here
      #redirect_to "https://www.google.com/calendar/render?pli=1" 
    end
  end
  
  def active_stream
    @on = params[:on]
    if @on == "true"
      @@active_stream = true
    else
      @@active_stream = false
    end
  end
  
  def streaming
    @active_stream = @@active_stream
  end
  
  def stream_active
    @active_stream = @@active_stream
    render :json => @active_stream
  end
end
