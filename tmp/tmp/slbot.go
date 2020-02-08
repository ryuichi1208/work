var attachment = slack.Attachment{
     Text:       "Which beer do you want? :beer:",
     Color:      "#f9a41b",
     CallbackID: "beer",
     Actions: []slack.AttachmentAction{
         {
             Name: actionSelect,
             Type: "select",
             Options: []slack.AttachmentActionOption{
                 {
                     Text:  "Asahi Super Dry",
                     Value: "Asahi Super Dry",
                 },
                 {
                     Text:  "Kirin Lager Beer",
                     Value: "Kirin Lager Beer",
                 },
                 {
                     Text:  "Sapporo Black Label",
                     Value: "Sapporo Black Label",
                 },
                 {
                     Text:  "Suntory Malt's",
                     Value: "Suntory Malts",
                 },
                 {
                     Text:  "Yona Yona Ale",
                     Value: "Yona Yona Ale",
                 },
             },
         },

         {
             Name:  actionCancel,
             Text:  "Cancel",
             Type:  "button",
             Style: "danger",
         },
     },
 }
 
 func (h interactionHandler) ServeHTTP(w http.ResponseWriter, r *http.Request) {
     if r.Method != http.MethodPost {
         log.Printf("[ERROR] Invalid method: %s", r.Method)
         w.WriteHeader(http.StatusMethodNotAllowed)
         return
     }

     buf, err := ioutil.ReadAll(r.Body)
     if err != nil {
         log.Printf("[ERROR] Failed to read request body: %s", err)
         w.WriteHeader(http.StatusInternalServerError)
         return
     }

     jsonStr, err := url.QueryUnescape(string(buf)[8:])
     if err != nil {
         log.Printf("[ERROR] Failed to unespace request body: %s", err)
         w.WriteHeader(http.StatusInternalServerError)
         return
     }

     var message slack.AttachmentActionCallback
     if err := json.Unmarshal([]byte(jsonStr), &message); err != nil {
         log.Printf("[ERROR] Failed to decode json message from slack: %s", jsonStr)
         w.WriteHeader(http.StatusInternalServerError)
         return
     }

     // Only accept message from slack with valid token
     if message.Token != h.verificationToken {
         log.Printf("[ERROR] Invalid token: %s", message.Token)
         w.WriteHeader(http.StatusUnauthorized)
         return
     }
     ....
}

func (h interactionHandler) ServeHTTP(w http.ResponseWriter, r *http.Request) {
     ....
     action := message.Actions[0]
     switch action.Name {
     case actionSelect:
         value := action.SelectedOptions[0].Value

         // Overwrite original drop down message.
         originalMessage := message.OriginalMessage
         originalMessage.Attachments[0].Text = fmt.Sprintf("OK to order %s ?", strings.Title(value))
         originalMessage.Attachments[0].Actions = []slack.AttachmentAction{
             {
                 Name:  actionStart,
                 Text:  "Yes",
                 Type:  "button",
                 Value: "start",
                 Style: "primary",
             },
             {
                 Name:  actionCancel,
                 Text:  "No",
                 Type:  "button",
                 Style: "danger",
             },
         }

         w.Header().Add("Content-type", "application/json")
         w.WriteHeader(http.StatusOK)
         json.NewEncoder(w).Encode(&originalMessage)
         return
     case actionStart:
         title := ":ok: your order was submitted! yay!"
         responseMessage(w, message.OriginalMessage, title, "")
         return
     case actionCancel:
         title := fmt.Sprintf(":x: @%s canceled the request", message.User.Name)
         responseMessage(w, message.OriginalMessage, title, "")
         return
     default:
         log.Printf("[ERROR] ]Invalid action was submitted: %s", action.Name)
         w.WriteHeader(http.StatusInternalServerError)
         return
     }
}

 func responseMessage(w http.ResponseWriter, original slack.Message, title, value string) {
     original.Attachments[0].Actions = []slack.AttachmentAction{} // empty buttons
     original.Attachments[0].Fields = []slack.AttachmentField{
         {
             Title: title,
             Value: value,
             Short: false,
         },
     }

     w.Header().Add("Content-Type", "application/json")
     w.WriteHeader(http.StatusOK)
     json.NewEncoder(w).Encode(&original)
 }
