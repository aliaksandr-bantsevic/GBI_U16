object Form_data_enter: TForm_data_enter
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = #1042#1074#1077#1076#1080#1090#1077' '#1076#1072#1085#1085#1099#1077
  ClientHeight = 90
  ClientWidth = 199
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'Tahoma'
  Font.Style = [fsBold]
  OnCreate = FormCreate
  TextHeight = 16
  object Button_apply: TButton
    Left = 8
    Top = 58
    Width = 90
    Height = 25
    Caption = #1055#1088#1080#1084#1077#1085#1080#1090#1100
    TabOrder = 0
    OnClick = Button_applyClick
  end
  object Button_cancel: TButton
    Left = 104
    Top = 58
    Width = 91
    Height = 25
    Caption = #1054#1090#1084#1077#1085#1072
    TabOrder = 1
    OnClick = Button_cancelClick
  end
  object Edit_data: TEdit
    Left = 8
    Top = 8
    Width = 185
    Height = 24
    TabOrder = 2
  end
end
