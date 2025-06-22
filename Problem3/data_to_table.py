import pandas as pd

def analyze_and_generate_latex(filename="results.csv"):
    """
    Wczytuje wyniki, analizuje je i generuje szczegółową tabelę w LaTeX,
    która na pewno zmieści się na stronie.
    """
    try:
        df = pd.read_csv(filename)
    except FileNotFoundError:
        print(f"Błąd: Plik '{filename}' nie został znaleziony.")
        return

    # Definiujemy wszystkie kolumny do uśrednienia
    cols_to_avg = ['Cmax', 'ReferenceCmax', 'AbsoluteError', 'RelativeError(%)', 'Time(ms)']

    # Grupujemy i liczymy średnią
    avg_results = df.groupby(['n', 'm', 'Algorithm'])[cols_to_avg].mean()

    # Przekształcamy tabelę - to da nam kolumny wielopoziomowe ('Cmax', 'NEH'), ('Cmax', 'FNEH') itd.
    unstacked_results = avg_results.unstack(level='Algorithm')

    # Przywracamy 'n' i 'm' jako zwykłe kolumny
    final_table_data = unstacked_results.reset_index()

    # Zmieniamy nazwy kolumn wielopoziomowych na pojedyncze, żeby łatwiej je wybrać
    final_table_data.columns = [f'{metric}_{algo}' for metric, algo in final_table_data.columns]

    # Ustawiamy ostateczną kolejność kolumn w tabeli
    final_table_ordered = final_table_data[[
        'n_','m_', # Nazwy złączone przez pandas, bierzemy te
        'Cmax_NEH', 'ReferenceCmax_NEH', 'AbsoluteError_NEH', 'RelativeError(%)_NEH', 'Time(ms)_NEH',
        'Cmax_FNEH', 'ReferenceCmax_FNEH', 'AbsoluteError_FNEH', 'RelativeError(%)_FNEH', 'Time(ms)_FNEH'
    ]]

    # Tworzymy ładny, wielopoziomowy nagłówek dla LaTeX
    final_table_ordered.columns = pd.MultiIndex.from_tuples([
        ('Instancja', 'n'), ('Instancja', 'm'),
        ('Algorytm NEH', 'Cmax'), ('Algorytm NEH', 'Ref. Cmax'), ('Algorytm NEH', 'Błąd abs.'),
        ('Algorytm NEH', 'Błąd [%]'), ('Algorytm NEH', 'Czas [ms]'),
        ('Algorytm FNEH (przyspieszony)', 'Cmax'), ('Algorytm FNEH (przyspieszony)', 'Ref. Cmax'),
        ('Algorytm FNEH (przyspieszony)', 'Błąd abs.'), ('Algorytm FNEH (przyspieszony)', 'Błąd [%]'),
        ('Algorytm FNEH (przyspieszony)', 'Czas [ms]')
    ])

    # Generujemy kod LaTeX
    latex_output = final_table_ordered.to_latex(
        index=False,
        booktabs=True,
        float_format="%.2f",
        caption="Szczegółowe porównanie średnich wyników algorytmów NEH i FNEH.",
        label="tab:neh_fneh_final_detailed",
        column_format="@{}rr|rrrrr|rrrrr@{}", # Formatowanie z liniami pionowymi
        escape=False
    )

    # Dodajemy \resizebox
    final_latex_code = (
        "\\begin{table}[h!]\n"
        "\\centering\n"
        f"\\caption{{{final_table_ordered.attrs.get('caption', '')}}}\n"
        f"\\label{{{final_table_ordered.attrs.get('label', '')}}}\n"
        "\\resizebox{\\textwidth}{!}{\n"
        f"{latex_output.splitlines()[3:-2][0]}\n" # Tylko wnętrze tabular
        "}\n"
        "\\end{table}"
    )

    # Usuwamy z kodu pandas niepotrzebne nagłówki, bo \resizebox tego nie lubi
    # (jest to bardziej zaawansowana operacja na stringach, ale daje pewny wynik)
    tabular_content = latex_output.split('\\midrule')[1].split('\\bottomrule')[0].strip()
    header_part1 = latex_output.split('\\toprule')[1].split('\\midrule')[0].strip()

    final_latex_code_manual = (
        "\\begin{table}[h!]\n"
        "\\centering\n"
        "\\caption{Szczegółowe porównanie średnich wyników algorytmów NEH i FNEH.}\n"
        "\\label{tab:neh_fneh_final_detailed}\n"
        "\\resizebox{\\textwidth}{!}{\n"
        "\\begin{tabular}{@{}rr|rrrrr|rrrrr@{}}\n"
        "\\toprule\n"
        f"{header_part1}\n"
        "\\midrule\n"
        f"{tabular_content}\n"
        "\\bottomrule\n"
        "\\end{tabular}\n"
        "}\n"
        "\\end{table}"
    )


    print(final_latex_code_manual)
#
# if __name__ == "__main__":
#     analyze_and_generate_latex()