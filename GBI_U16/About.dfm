object Form_about: TForm_about
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = #1054' '#1087#1088#1086#1075#1088#1072#1084#1084#1077' GBI16'
  ClientHeight = 173
  ClientWidth = 332
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -15
  Font.Name = 'Tahoma'
  Font.Style = [fsBold]
  OnCreate = FormCreate
  TextHeight = 18
  object Label_version: TLabel
    Left = 87
    Top = 19
    Width = 107
    Height = 18
    Caption = 'Label_version'
    Layout = tlCenter
  end
  object Label2: TLabel
    Left = 87
    Top = 43
    Width = 151
    Height = 18
    Caption = 'www.ntpgorizont.ru'
  end
  object Label_year: TLabel
    Left = 87
    Top = 67
    Width = 85
    Height = 18
    Caption = 'Label_year'
    Layout = tlCenter
  end
  object Button_close: TButton
    Left = 110
    Top = 104
    Width = 105
    Height = 25
    Caption = #1047#1072#1082#1088#1099#1090#1100
    TabOrder = 0
    OnClick = Button_closeClick
  end
end
